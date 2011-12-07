<?php
/*
 * Function to get location data
 */
function cloud360_getLocation($lid) {
  return _cloud360_get_object('getPhotographyLocation', NULL, array('filter' => array('uid' => $lid)));
}
/*
 * Function to get 360 image data
 */
function cloud360_get360($nid) {
  return _cloud360_get_object('getPanoramicPhotography', NULL, array('filter' => array('uid' => $nid)));
}
/*
 * Function to create the coverflow
 */
function cloud360_render_coverflow() {
  //_test_aip();
  //Get language
  global $language;
  //Build html for coverflow
  $result = '<div id="myimageflow" class="imageflow"><div id="myloader" class="coverflow-loader"></div>';
  //Get image list
  $images = variable_get('cloud360_categories_'.$language->language);
  //Render Coverflow
  foreach($images as $image) {
    //download image
    $imagePath = _cloud360_download_image($image['imageUrl'], 'sites/default/files/coverflow/'.$image['uid']);
    $lang = '';
    if($language->language != 'en')
     $lang = '/'.$language->language.'/';
    //Create image
    $img = '<img src="'.$imagePath.'" longdesc="'.$lang.'content/category-result?category='.$image['uid'].'" width="300" height="217" alt="'.$image['name'].'"></img>';
    //Add image to result
    $result .= $img;
  }
  $result .= '</div>';

  return $result;
}
/*
 * Function to create the map
 */
function cloud360_render_map360() {
  //Set map default values
  $parameters = array ('id' => 'map360',
                     'zoom' => 7,
                    'width' => '100%',
                   'height' => '456px',
                  'maptype' => 'Map',
              'controltype' => 'Large',
                'longitude' => -78.706055,
                 'latitude' => -1.30726,
        'streetViewControl' => TRUE,
                  'markers' => '',
       ) ;
  //return map
  return _cloud360_render_map($parameters);
}
/*
 * Function to render the category result
 */
function cloud360_render_category_result() {
  global $language;

  $result = '';
  if($_GET['category']) {
    //Recover categories from url parameters
    $categories = array();
    if($_GET['category'] == 'all') {
      $categories = _cloud360_get_all_categories_exclude_sustenaible();
    }
    else {
      foreach(explode(',', $_GET['category']) as $item) {
        $categories[] = intval($item);
      }
    }
    //Recover Panoramics
    $post = array('filter'=> array('categories' => $categories,
                                     'pageSize' => 50,
                                        'start' => 0));

    $panoramics = _cloud360_get_object('searchRank', NULL, $post);
    //Render panoramic by category
    foreach($panoramics['results'] as $item) {
      $panoramic = cloud360_getLocation($item['uid']);
      foreach($categories as $category) {
        if($panoramic) {
          if(in_array($category, $panoramic['categories'])) {
            $result .= _cloud360_render_panoramic($panoramic);
          }
        }
      }
    }
    
  }
  
  return '<div class="result-wrapper">'.$result.'</div>';
}
/*
 * HELPERS
 */
//Function to load data from cloud services
function _cloud360_get_object($api, $parameters = NULL, $postParameters = NULL) {
  //Instance cloud360 service class
  $cloud = new class_cloud360_service_data($api, $parameters, $postParameters);
  return $cloud->getApiData();
}
//Function to generate the map data
function _cloud360_render_map($parameters = NULL, $macro = NULL) {
  //Instance cloud360 map class
  $map = new class_cloud360_gmap($parameters, $macro);
  $categories = _cloud360_get_all_categories();
  //Add markers
  $zlevel = 1;
  while($zlevel < 7) {
    $postParameters = array('filter'=> array('categories' => $categories,
                         'landmark' => array(-1.30726, -78.706055),
                          'radious' => 90000,
                           'zlevel' => $zlevel));
    $markers = _cloud360_get_object('getLandmark', NULL, $postParameters);

    if($markers != 'null') {
      foreach ($markers['results'] as $marker) {
        //Add Marker
        if($marker['type'] == 1) {
          $category = _cloud360_get_category_name($marker['categories'][0]);
          if(!$category) {
            $category = _cloud360_get_category_name($marker['categories'][1]);
          }
        }
        else {
          $category = ' ';
        }

        $map->addMarker($marker['type'],
                        $marker['uid'],
                        str_replace(' ', '_', strtolower($category)),
                        $marker['landmark']['0'],
                        $marker['landmark']['1'],
                        $marker['title'],
                        $category);
      }
    }
    $zlevel += 1;
  }

  return $map->displayMap();
}
//Function to save images
function _cloud360_download_image($url, $filesDir) {
  //Var to set the path tyo store images
  //$filesDir = 'sites/default/files/coverflow/'.$uid;
  //Var to return the path of the image
  $imagePath = '';
  //Validate if the folder can be created
  $validate = true;
  if (!file_prepare_directory($filesDir)) {
    if (!drupal_mkdir($filesDir, NULL, TRUE, NULL)) {
      $validate = FALSE;
    }
  }

  if($validate) {
    //Recover image path from url parameters
    foreach (explode('/', $url) as $value) {
      $imageName = $value;
    }
    $imagePath = $filesDir.'/'.$imageName;
    //Validate if the image exist
    if (!file_exists($imagePath)) {
      //Set curl options
      $defaults = array(
            CURLOPT_URL => $url,
            CURLOPT_HEADER => 0,
            CURLOPT_RETURNTRANSFER => TRUE,
            //CURLOPT_TIMEOUT => 4,
            CURLOPT_SSL_VERIFYPEER => FALSE
      );
      //init curl
      $ch = curl_init();
      curl_setopt_array($ch, $defaults);
      $rawdata=curl_exec($ch);
      curl_close ($ch);
      //Write image
      $fp = fopen($imagePath,'x');
      fwrite($fp, $rawdata);
      fclose($fp);
    }
  }

  return $imagePath;
}
/*
 * Function to get an array of all categories
 */
function _cloud360_get_all_categories() {
  global $language;
  $result = array();
  //Get catagories var
  $categories = variable_get('cloud360_categories_'.$language->language);
  foreach($categories as $category) {
    $result[] = $category['uid'];
  }
  
  return $result;
}
/*
 * Function to get an array of all categories
 */
function _cloud360_get_all_categories_exclude_sustenaible() {
  global $language;
  $result = array();
  //Get catagories var
  $categories = variable_get('cloud360_categories_'.$language->language);
  foreach($categories as $category) {
    if($category['uid'] != 109) {
      $result[] = $category['uid'];
    }
  }
  
  return $result;
}
/*
 * Function to get the icon
 */
function _cloud360_get_category_name($category_id) {
  global $language;
  $result = '';
  //Get catagories var
  $categories = variable_get('cloud360_categories_'.$language->language);
  foreach($categories as $category) {
    if($category['uid'] == $category_id) {
      $result = $category['name'];
    }
  }
  return $result;
}
/*
 * Function to get category the icon
 */
function _cloud360_get_category_icon($category_id) {
  global $language;
  $result = '';
  //Get catagories var
  $categories = variable_get('cloud360_categories_'.$language->language);
  foreach($categories as $category) {
    if($category['uid'] == $category_id) {
      $result = $category['iconName'];
    }
  }
  return $result;
}
/*
 * Function to get the server image path
 */
function _cloud360_get_server_image_path($image) {
  return variable_get('cloud360_imagesUrl').$image;
}
/*
 * Function to render an image
 */
function _cloud360_render_image($image) {
  return '<img src="'.$image.'" alt="NO IMAGE FOUND" />';
}
/*
 * Function to get the region
 */
function _cloud360_get_region($rid) {
  global $language;
  $result = variable_get('cloud360_regions_'.$language->language);
  return $result[$rid]['name'];
}
/*
 * Function to render the catagory filter on the map
 */
function _cloud360_render_catedories_map() {
  global $language;
  $result = '';
  //Get image list
  $categories = variable_get('cloud360_categories_'.$language->language);
  //Close Button
  $result .= '<div class="map-close-button "><a class="open" href="javascript:map_close();">Close</a></div>';
  $result .= '<div class="map-footer-wrapper">';
  //Option ALL
  $variables = array('title'=>'' ,
                      'path'=>drupal_get_path('theme', 'ecuador360').'/images/all.png', 
                       'alt'=>'NO ICON', 
                    'height'=>'', 
                     'width'=>'',
                'attributes'=>'');
  $result .=   '<div class="category">';
  $result .=     '<div class="check"><input type="checkbox" name="all" id="-1" checked="checked"></div>';
  $result .=     '<div class="icon">'.theme_image($variables).'</div>';
  $result .=     '<div class="title">'.strtolower(_cloud360_map_all_category_text()).'</div>';
  $result .=   '</div>';

  foreach($categories as $category) {
    if(array_key_exists('iconUrl', $category)) {
      $result .= '<div class="category">';
      $result .= '<div class="check"><input type="checkbox" name="'.$category['uid'].'" id="'.$category['uid'].'"></div>';
      $result .= '<div class="icon"><img src="'.$category['iconUrl'].'" alt="No Icon"></img></div>';
      $result .= '<div class="title" rel="'._cloud360_map_get_category_icon($category['uid']).'">'.strtolower($category['name']).'</div>';
      $result .= '</div>';
    }
  }
  //Filter Button
  $result .= '<div class="category-button">';
  $result .= '<div class="filter"><input id="map-filter" type="submit" name="Filter" id="100" value="'._cloud_map_filter_text().'"></div>';
  $result .= '</div>';
  $result .= '</div>';
  return $result;
}

function _cloud360_map_get_category_icon($category_id) {
  return _cloud360_get_category_icon($category_id);
}

function _cloud360_map_form($form, &$form_state) {
  //Activities field
  $form['selected'] = array(
    '#type' => 'select',
    '#title' => 'Activities',
    '#multiple' => TRUE,
    '#options' => array('asd' => 'asd',
                    'asertwe' => 'vaga'),
  );

  return $form;
}

function _cloud360_map_all_category_text() {
  global $language;
  $languageServices = array('es' => 'Todos',
                            'en' => 'All');

  return $languageServices[$language->language];
}

function _cloud_map_filter_text() {
  global $language;
  $languageServices = array('es' => 'Filtrar',
                            'en' => 'Filter');

  return $languageServices[$language->language];
}

/*
 * Function to render error on cloud data
 */
function _cloud360_error() {
  $error = drupal_get_messages();

  $content = array(
      '#type' => 'markup',
      '#prefix' => '<div class="error-wrapper">',
      '#markup' => '<div class="error-code">Se ha producido un error</div><div class="error-message"></div>',
      '#suffix' => '</div>',
  );

  if(array_key_exists('status', $error)) {
    $content = array();
    foreach ($error['status'] as $value) {
      $content[] = array(
          '#type' => 'markup',
          '#prefix' => '<div class="error-wrapper">',
          '#markup' => '<div class="error-code">'.$value['code'].'</div><div class="error-message">'.$value['message'].'</div>',
          '#suffix' => '</div>',
      );
    }
  }

  return drupal_render($content);
}

/*
 * Function to create gmap markers from categories
 */
function _cloud360_build_gmap_markers(&$categories, $language) {
  //Get gmap module path
  $path = drupal_get_path('module', 'gmap');
  
  if($path) {
    //Add ecuador360 markers folder
    $path .= '/markers/ecuador360/';
    //Validate if the folder can be created
    $validate = TRUE;
    if (!file_prepare_directory($path)) {
      if (!drupal_mkdir($path, NULL, TRUE, NULL)) {
        $validate = FALSE;
      }
    }

    if($validate) {
      foreach($categories as $category) {
        //Validate if marker exsist
        $file_name = $category['uid'].'_'.$language.'.ini';
        $file = $path.'/'.$file_name;
        if(!file_exists($file)) {
          //Create INI file
          $ini_text = '[defaults]
anchorX = 10
anchorY = 29
infoX = 17
infoY = 6
['.str_replace(' ', '_', strtolower($category['name'])).']
name = "'.$category['name'].'"
sequence = "'.$category['iconName'].'"';
          
          //Write INI file
          $fp = fopen($file, 'w');
          fwrite($fp, $ini_text);
          fclose($fp);
          //Write icon
          _cloud360_download_image($category['iconUrl'], $path);
        }
      }
    }
  }
}
/*
 * Function to make a like vote
 */
function _cloud360_like() {
  _cloud360_vote(TRUE);
}
/*
 * Function to make a not like vote
 */
function _cloud360_not_like() {
  _cloud360_vote(FALSE);
}
/*
 * Function to add to favorites
 */
function _cloud360_favorites_360() {
  $entityId = $_GET['uid'];
  _cloud360_add_favorite(0, $entityId);
}
/*
 * Function to make a vote
 */
function _cloud360_vote($positive = TRUE) {
  global $user;
  $uid = $_GET['uid'];
  //Validate User and UID
  if($user->uid != 0 && $uid) {
    //Make Vote
    if(_cloud360_service_vote($positive, $uid)) {
      //Set vote message
      _cloud360_vote_get_message(TRUE);
      //Return to page
      drupal_goto('image360', array('query'=>array('pid'=>$uid)));
    }
    else {
      _cloud360_vote_get_message(FALSE);
      drupal_goto('cloud360/error');
    }
  }
  else {
    //Validate UID
    if($uid) {
      //Save session to redirect to 360 page
      $_SESSION['vote_360_uid'] = array('positive'=>$positive, 'uid'=>$uid) ;
      //Redirect to user login
      drupal_goto('user/login');
    }
    else {
      drupal_set_message(t('Error no existe la foto 360.'), 'error');
      drupal_goto('cloud360/error');
    }
  }
}
/*
 * Function to get the message to 
 */
function _cloud360_vote_get_message($positive = TRUE) {
  global $language;
  $default_messages = array('en'=>'Your vote has been registered.',
                            'es'=>'Su voto ha sido registrado.');

  $error_messages = array('en'=>'Your vote can not benn registered. Please try again later.',
                          'es'=>'Su voto no ha podido ser registrado. Por favor intentelo mas tarde.');
  if($positive) {
    $message = variable_get('cloud_360_vote_message_'.$language->language, $default_messages[$language->language]);
  }
  else {
    $message = array('code'=>'', 
                     'message'=>variable_get('cloud_360_vote_message_error_'.$language->language, $error_messages[$language->language]));
  }
  
  drupal_set_message($message);
}

function _cloud360_service_vote($positive, $entityID) {
  $api = 'userVote';
  $parameters = NULL;
  $postParameters = array('filter'=>array('vote' => $positive,
                                         'userId' => _cloud360_get_user_id(),
                                       'entityId' => $entityID,));
  
  $result = _cloud360_get_object($api, $parameters, $postParameters);

  if($result['value'] == 'success') {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

function _cloud360_my_favorites_360() {
  global $user;
  if($user->uid != 0) {
    $result = '<div class="page-title">'._cloud360_get_favorites_title().'</div>';
    
    $panoramics = _cloud360_get_favorites();

    foreach($panoramics['results'] as $panoramic) {
      $result .= _cloud360_render_panoramic($panoramic, 1);
    }

    if(!$result) {
      global $language;
      $def_text = array('en' => 'Please add some favorites!',
                        'es' => 'Por facor agrega favoritos!',);
      $result = variable_get('cloud_360_my_favorites_text_'.$language->language, $def_text[$language->language]);
    }

    return $result;
  }
  else {
    drupal_goto('user/login');
  }
}

function _cloud360_render_panoramic($panoramic, $favorite = 0) {
  $result = '';
  //Render panoramic by category
  if($panoramic) {
    $result .= '<div class="result-item">';
    $result .= '<div class="title">'.$panoramic['name'].'</div>';
    $result .= '<div class="region">'._cloud360_get_region($panoramic['region']).'</div>';
    $result .= '<div class="image">'.l(_cloud360_render_image($panoramic['imageUrl']),
            'image360',
            array('query' => array('pid' => $panoramic['uid'], 'fav' => $favorite),
                'html' => TRUE)).'</div>';
    $result .= '<div class="visits">'._cloud360_visits_text($panoramic['visits']).'</div>';
    $result .= '</div>';
  }

  return $result;
}

function _cloud360_visits_text($visits) {
  global $language;
  
  if ($language->language == 'en') {
    return $visits.' visits';
  }
  
  if ($language->language == 'es') {
    return $visits.' visitas';
  }
}

function _cloud360_add_favorite($type, $entityId) {
  global $user;
  if($user->uid != 0) {
    if($entityId) {
      $api = 'userAddFavorites';
      $postParameters = array('filter' => array('entityId' => $entityId,
                                                  'userId' => _cloud360_get_user_id(),
                                                   'fType' => $type,),);

      $favorite = _cloud360_get_object($api, NULL, $postParameters);

      if($favorite['value'] == 'success') {
        drupal_goto('myfavorites_360');
      }
      else {
        return 'Error';
      }
    } 
  }
  else {
    drupal_goto('user/login');
  }
}

function _cloud360_denounce_link($uid, $commentId) {
  global $user;
  if($user->uid != 0) {
    global $language;

    $text = array('en'=>'Denounce',
                  'es'=>'Denunciar',);

    return l($text[$language->language], 'denounce/comment', array('query'=>array('uid'=>$uid, 'commentId'=>$commentId)));
  }
  else {
    return '';
  }
}

function _cloud360_delete_link($uid, $commentId) {
  global $user;
  if($user->uid != 0) {
    global $language;

    $text = array('en'=>'Delete',
                  'es'=>'Eliminar',);

    return l($text[$language->language], 'delete/comment', array('query'=>array('uid'=>$uid, 'commentId'=>$commentId)));
  }
  else {
    return '';
  }
}

function _cloud360_denounce_comment() {
  $uid = $_GET['uid'];
  $commentId = $_GET['commentId'];
  //Denounce comment
  $api = 'userDenounceComment';
  $postParameters = array('filter' => array('text' => 'Por favor revisar este comentario no es apropiado',
                                          'userId' => _cloud360_get_user_id(),
                                        'entityId' => $uid,
                                       'commentId' => $commentId),);

  $denounce = _cloud360_get_object($api, NULL, $postParameters);
  //Set confirmation message
  global $language;
  $text = array('en'=>'The comment has been denonced',
                'es'=>'El comentario ha sido denunciado',);
  
  drupal_set_message($text[$language->language]);
  
  drupal_goto('image360', array('query'=>array('pid'=>$uid)));
}

function _cloud360_delete_comment() {
  $uid = $_GET['uid'];
  $commentId = $_GET['commentId'];
  //Denounce comment
  $api = 'userDeleteFavoritesComment';
  $postParameters = array('filter' => array('entityId' => $uid,
                                              'userId' => _cloud360_get_user_id(),
                                               'fType' => 0,
                                              'noteId' => $commentId),);

  $denounce = _cloud360_get_object($api, NULL, $postParameters);
  //Set confirmation message
  global $language;
  $text = array('en'=>'The comment has been deleted',
                'es'=>'El comentario ha sido eliminado',);
  
  drupal_set_message($text[$language->language]);
  
  drupal_goto('image360', array('query'=>array('pid'=>$uid)));
}

function _cloud360_news() {
//  if($language->language == 'es') {
//    drupal_goto('aggregator/categories/2');
//  }
//  else {
//    drupal_goto('aggregator/sources/2');
//  }
  
  return '';
}

function _cloud360_search() {
  global $language;
  
  $text = array('en'=>'Search results for "'.$_GET['text'].'"',
                'es'=>'Resultados de la busqueda de "'.$_GET['text'].'"');
  
  $result = '<div class="search-title">'.$text[$language->language]."</div>";
  $api = 'searchGeneral';
  $postParameters = array('filter' => array('categories' => _cloud360_get_all_categories(),
                                              'pageSize' => 100,
                                                 'start' => 0,
                                                  'term' => $_GET['text']),);

  $results = _cloud360_get_object($api, NULL, $postParameters);
  
  foreach ($results['results'] as $value) {
    $result .= '<div class="search-result">'.l($value['title'], 'image360', array('query'=>array('pid'=>$value['uid']))).'</div>';
  }
  
  
  return $result;
}

function _cloud360_get_map_zoom($zoom) {
  $maped_zoom = array();
  $maped_zoom[1] = 7;
  $maped_zoom[2] = 10;
  $maped_zoom[3] = 13;
  $maped_zoom[4] = 15;
  $maped_zoom[5] = 17;
  $maped_zoom[6] = 19;

  return $maped_zoom[$zoom];
}

function _cloud360_get_favorites_title() {
  global $language;
  $text = array('es'=>'Favoritos',
                'en'=>'Favorites');
  return $text[$language->language];
}


function _cloud360_get_favorites() {
  $_SESSION['cloud360_user_id'];
  //Get all Categories
  $categories = _cloud360_get_all_categories();
  //Get user id
  $uid = _cloud360_get_user_id();
  //Get user favorites
  $api = 'userFavorites';
  $postParameters = array('filter' => array('categories' => $categories,
                                              'pageSize' => 20,
                                                 'start' => 0,
                                                'userId' => $uid,
                                                'client' => 'WEB',));

  $_SESSION['ecuador360_user_favorites'] = _cloud360_get_object($api, NULL, $postParameters);
  
  return $_SESSION['ecuador360_user_favorites'];
}