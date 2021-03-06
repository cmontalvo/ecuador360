<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of class_build_krpano_xml
 *
 * @author cesar
 */

class class_krpano {
  //Variable to know if the panoramic is correct
  private $valid_data = TRUE;
  //Stop Recursive
  private $stop_recursive = TRUE;
  //Var to store the languaje
  private $lan;
  //Path to krpano module
  private $krpanoPath = '';
  //Path to xml files
  private $xmlPath = 'sites/default/files/';
  //Potography id
  private $pid;
  //Location infokrumo
  private $location_info;
  //Near Locations
  private $map_spots = array();
  //Var to store the detail messages translations
  private $detail_messages = array('information' => array('en' => 'Information',
                                                          'es' => 'Información'),
                                   'coordinates' => array('en' => 'GPS Coordinates: ',
                                                          'es' => 'Coordenadas GPS: ' ),
                                       'alitude' => array('en' => 'Alitude: ',
                                                          'es' => 'Altitud: '),
                                       'company' => array('en' => 'Company: ',
                                                          'es' => 'Companía: '),
                                   'description' => array('en' => 'Description: ',
                                                          'es' => 'Descripción: '),
                                       'address' => array('en' => 'Address: ',
                                                          'es' => 'Dirección: '),
                                         'phone' => array('en' => 'Phone: ',
                                                          'es' => 'Teléfono: '),
                                           'fax' => array('en' => 'Fax: ',
                                                          'es' => 'Fax: '),
                                           'web' => array('en' => 'Web: ',
                                                          'es' => 'Web: '),
                                         'email' => array('en' => 'Email: ',
                                                          'es' => 'Email: '),
                                      'pcredits' => array('en' => 'Photo Credits: ',
                                                          'es' => 'Créditos fotográficos: '),
                                         'share' => array('en' => 'Share',
                                                          'es' => 'Compartir'),
                                          'like' => array('en' => 'I like',
                                                          'es' => 'Me gusta'),
                                       'notLike' => array('en' => 'I don\'t like',
                                                          'es' => 'No me gusta'),
                                     'favorites' => array('en' => 'Send to favorites',
                                                          'es' => 'Enviar a favoritos'),
                                      'facebook' => array('en' => 'Facebook: ',
                                                          'es' => 'Facebook: '),
                                         'tweet' => array('en' => 'tweet: ',
                                                          'es' => 'tweet: '),
                                         'skype' => array('en' => 'Skype: ',
                                                          'es' => 'Skype: '),
                                       'twitter' => array('en' => 'Tweeter: ',
                                                          'es' => 'Tweeter: '),
                                      'comments' => array('en' => 'Comments',
                                                          'es' => 'Comentarios'),
                            'favorites_comments' => array('en' => 'Favorites Comments',
                                                          'es' => 'Comentarios Favoritos'),
                                 'leave_comment' => array('en' => 'Please register to leave your commnets.',
                                                          'es' => 'Por favor registrate para dejar tus comentarios.')
                                  );

  private $gmap_plugin = array('name' => 'map',
                            'visible' => 'false',
                                'url' => '%SWFPATH%/plugins/googlemaps.swf',
                               'keep' => 'true',
                         'handcursor' => 'false',
                              'align' => 'lefttop',
                                  'x' => '10',
                                  'y' => '10',
                              'width' => '350',
                             'height' => '410',
                                'key' => '',
                                'lat' => '-0.285233',
                                'lng' => '-90.555961',
                               'zoom' => '',
                            'maptype' => 'normal',
                           'dragging' => 'true',
                        'scrollwheel' => 'true',
                     'continuouszoom' => 'false',
                           'keyboard' => 'false',
                         'crosshairs' => 'false',
                         'onmapready' => '',
                         'onmapmoved' => '',
                        'onmapzoomed' => '',);

  private $radar = array('visible' => 'true',
                            'size' => '100',
                           'alpha' => '0.5',
                       'fillcolor' => 'xFFFFFF',
                       'fillalpha' => '1.0',
                       'linecolor' => '0xFFFFFF',
                       'linealpha' => '0.0',
                       'linewidth' => '0.0',
                            'glow' => 'true',
                       'glowcolor' => '0xFFFFFF',
                       'glowwidth' => '4',
                    'glowstrength' => '3',
                     'behindspots' => 'true',
                        'dragable' => 'true',);

  private $positioncontrol = array('visible' => 'true',
    	                                   'x' => '2',
	                                       'y' => '2');

  private $zoomcontrol = array('visible' => 'true',
	                              'anchor' => 'topright',
	                      'hasscrolltrack' => 'true',
	                                   'x' => '2',
	                                   'y' => '2');

  private $spot = array('name' => 's1',
	                       'lat' => '-0.285233',
	                       'lng' => '-90.555961',
	                   'onhover' => 'showtext(\'360Title\');',
	                   'onclick' => 'action(s1);',
	                   'heading' => '0',
	                    'active' => 'flase',
                         'url' => '');

  private $include = array('url' => '%SWFPATH%/skin/defaultskin.xml');

  private $view = array('hlookat' => '0',
	                      'vlookat' => '0',
      	                    'fov' => '90',
                         'fovmin' => '40',
	                       'fovmax' => '110',
	                      'fisheye' => '0',
                   'maxpixelzoom' => '3.0'
      );

  private $display = array('details' => '22');

  private $preview = array('type' => 'CUBESTRIP',
	                          'url' => 'GLP06.tiles/preview.jpg');

  private $image = array('type' => 'CUBE',
	                   'multires' => 'true',
	                   'tilesize' => '4000');

  private $level = array('tiledimagewidth' => '512',
	                      'tiledimageheight' => '512');

  private $left = array('url' => 'GLP06.tiles/l_%0v_%0h.jpg');

  private $front = array('url' => 'GLP06.tiles/f_%0v_%0h.jpg');

  private $right = array('url' => 'GLP06.tiles/r_%0v_%0h.jpg');

  private $back = array('url' => 'GLP06.tiles/b_%0v_%0h.jpg');

	private $up = array('url' => 'GLP06.tiles/u_%0v_%0h.jpg');

	private $down = array('url' => 'GLP06.tiles/d_%0v_%0h.jpg');
  
  private $hot_spots = array();

  private $infotext = array('name' => 'info_text',
                             'url' => '%SWFPATH%/plugins/hotspot.swf',
                         'imgurl1' =>  'https://s3.amazonaws.com/captur-images/2_l.jpg',
                       'headtitle' =>  'Hotel Palace Guayaquil - Hotspot1',
                           'align' => 'top',
                           'width' => '409',
                          'height' => '360',
                               'x' => '0',
                               'y' => '10',
                     'borderwidth' => '0',
                            'glow' => '4',
                 'backgroundcolor' => '0x000000',
                      'selectable' => 'false',
                         'visible' => 'false',
                          'shadow' => '5');

  private $show_infotext = array('name' => 'show_info_text');

  private $hotSpot = array('name' => 'spot',
                        'onclick' => 'action(show_info_text,info_text1,\'data:htmldata1\');',
                            'url' => '%SWFPATH%/skin/info.png',
                            'ath' => '0',
                            'atv' => '0');

  private $hotSpotData = array('name' => 'htmldata');

  private $hotSpotDataDetail =  '<p align="left">
           	Nuestro servicio y cordialidad nos convierte en el lugar predilecto de
			ejecutivos y turistas  que buscan una atmósfera familiar y calidad en los detalles en la mejor ubicación de la ciudad.
            <br />
          </p>
		  <p align="left">
			 Web: <a href="event:js(mypopup(http://www.hotelpalaceguayaquil.com.ec);return false;)">www.hotelpalaceguayaquil.com.ec</a> <br/>
			 Email: <a href="mailto:info@hotelpalaceguayaquil.com.ec">info@hotelpalaceguayaquil.com.ec</a><br/>
		   </p>';

  private $degree_conf = array('en' => array( 'v' => array('pos' => 'N',
                                                           'neg' => 'S'),
                                              'h' => array('pos' => 'E',
                                                           'neg' => 'W')),
                               'es' => array( 'v' => array('pos' => 'N',
                                                           'neg' => 'S'),
                                              'h' => array('pos' => 'E',
                                                           'neg' => 'O')),
                              );
  
  private $no_error_log = array('showerrors' => 'false');

  public function __construct($pid, $near_spots = TRUE) {
    if ($pid) {
      //Stop Recursive
      $this->stop_recursive = $near_spots;
      //Set language
      global $language;
      $this->lan = $language->language;
      //Set swf path
      $this->krpanoPath = drupal_get_path('module', 'krpano');
      //Set xml path
      $this->xmlPath = drupal_get_path('module', 'krpano').'/panoramas/';
      //Set google map key from variable
      $this->gmap_plugin['key'] = variable_get('googlemap_api_key');
      //Set potography object id
      $this->pid = $pid;
      //Recober nid info
      $this->_krpano_get_info($near_spots);
    }
  }

  public function krpano_render() {
    $resutlt = '';
    //Add krpano scripts
    drupal_add_js($this->krpanoPath.'/fla/swfkrpano.js');

    drupal_add_js('jQuery(document).ready(function(){
                   var viewer = createPanoViewer({swf:"/'.$this->krpanoPath.'/fla/krpano.swf",target:"krpano-div"});
                   viewer.addVariable("xml", "/'.$this->krpanoPath.'/panoramas/'.$this->pid.'.xml");
                   viewer.embed();
                   });', 'inline');
    
    $resutlt = '<div id="krpano-div" style="height:425px;">
               	<noscript><table style="width:100%;height:100%;"><tr style="valign:middle;"><td><div style="text-align:center;">ERROR:<br/><br/>Javascript not activated<br/><br/></div></td></tr></table></noscript>
                </div>';

    $resutlt .= $this->location_info;

    return $resutlt;
  }

  public function krpano_create_xml() {
    $doc = new DOMDocument('1.0', 'ISO-8859-1');
    $root = $doc->appendChild($doc->createElement('krpano'));
    //Add no show errors
    $plugin_root = $this->_krpano_add_xml_node($root, $doc, 'krpano', $this->no_error_log);
    //Add plugin
    $plugin_root = $this->_krpano_add_xml_node($root, $doc, 'plugin', $this->gmap_plugin);
    //Add radar
    $this->_krpano_add_xml_node($plugin_root, $doc, 'radar', $this->radar);
    //Add postcontrol
    $this->_krpano_add_xml_node($plugin_root, $doc, 'positioncontrol', $this->positioncontrol);
    //Add zoom control
    $this->_krpano_add_xml_node($plugin_root, $doc, 'zoomcontrol', $this->zoomcontrol);
    //Add spot
    $this->_krpano_set_spot($root, $plugin_root, $doc);
    //Add include
    $this->_krpano_add_xml_node($root, $doc, 'include', $this->include);
    //Add view
    $this->_krpano_add_xml_node($root, $doc, 'view', $this->view);
    //Add display
    $this->_krpano_add_xml_node($root, $doc, 'display', $this->display);
    //Add preview
    $this->_krpano_add_xml_node($root, $doc, 'preview', $this->preview);
    //Add image
    $image_root = $this->_krpano_add_xml_node($root, $doc, 'image', $this->image);
    //Add level
    $level_root = $this->_krpano_add_xml_node($image_root, $doc, 'level', $this->level);
    //Add left
    $this->_krpano_add_xml_node($level_root, $doc, 'left', $this->left);
    //Add front
    $this->_krpano_add_xml_node($level_root, $doc, 'front', $this->front);
    //Add right
    $this->_krpano_add_xml_node($level_root, $doc, 'right', $this->right);
    //Add back
    $this->_krpano_add_xml_node($level_root, $doc, 'back', $this->back);
    //Add up
    $this->_krpano_add_xml_node($level_root, $doc, 'up', $this->up);
    //Add down
    $this->_krpano_add_xml_node($level_root, $doc, 'down', $this->down);
    //Add show infotext acction
    $show_infotext_action = $root->appendChild($doc->createElement('action'));
    $show_infotext_action->setAttribute('name',  'show_info_text');
    $show_infotext_action->appendChild($doc->createTextNode('set(plugin[info_button].enabled,false); set(plugin[%1].alpha,0); set(plugin[%1].textblur,15); set(plugin[%1].blur,15);
    	set(plugin[%1].visible,true); set(plugin[%1].enabled,true);
	    tween(plugin[%1].alpha,1,0.3); tween(plugin[%1].textblur,0,0.3); tween(plugin[%1].blur,0,0.3); set(plugin[%1].html,%2);'));
    //Add hotspots
    $this->_krpano_render_hot_spots($root, $doc);
    
    $doc->saveHTML();
    $doc->save($this->xmlPath.$this->pid.'.xml') . 'bytes';
  }

  private function _krpano_get_info($near_spots) {
    //Get Potography Info
    $location = cloud360_getLocation($this->pid);
    if (is_array($location)) {
      //Get 360 Data
      $image360 = cloud360_get360($location['photography']);
      //Get Zlevel
      $radious = 1;
      if($near_spots) {
        $radious = 40;
      }
      $postParameters = array('filter'=> array('categories' => _cloud360_get_all_categories(),
                           'landmark' => array($location['landMark']['latitude'], 
                                               $location['landMark']['longitude']),
                            'radious' => $radious,
                             'zlevel' => 7));
      $location_search = _cloud360_get_object('getLandmark', NULL, $postParameters);
      foreach($location_search['results'] as $key => $value) {
        $value['cone'] = FALSE;
        $value['order'] = $key + 10;
        if($location['uid'] == $value['uid']) {
          $zlevel = $value['zlevel'];
          $value['cone'] = TRUE;
          $value['heading'] = $image360['heading'];
          $value['order'] = 0;
        }
        $this->map_spots[] = $value;
      }
      //Order Spots
      sort($this->map_spots);
      //Get Hot Spots
      $this->hot_spots = $image360['hotspots'];
      //Get Module path
      $path = drupal_get_path('module', 'krpano');
      //Set images
      $this->left['url']    = $image360['images']['left'];
      $this->front['url']   = $image360['images']['front'];
      $this->right['url']   = $image360['images']['right'];
      $this->back['url']    = $image360['images']['back'];
      $this->up['url']      = $image360['images']['up'];
      $this->down['url']    = $image360['images']['down'];
      $this->preview['url'] = $image360['images']['preview'];
      //Set zoom properties
      $this->view['hlookat'] = $image360['camera']['hlookat'];
      $this->view['vlookat'] = $image360['camera']['vlookat'];
      //Set map properties
      $this->gmap_plugin['lat'] = $location['landMark']['latitude'];
      $this->gmap_plugin['lng'] = $location['landMark']['longitude'];
      $this->gmap_plugin['zoom'] = _cloud360_get_map_zoom($zlevel);
      //Generate location info
      $this->location_info = $this->_krpano_detail_info($location);
    } 
    else {
      $this->valid_data = FALSE;
      watchdog('cloud360', 'Error Loading Panorama PID = ' . $this->pid);
    }
  }

  private function _krpano_add_xml_node(&$root, &$doc, $container, $elements) {
    $xmlContainer = $root->appendChild($doc->createElement($container));

    foreach ($elements as $key => $value) {
      $xmlContainer->setAttribute($key, $value);
    }

    return $xmlContainer;
  }

  private function _krpano_add_datatxt(&$root, &$doc){
    $data_root = $this->_krpano_add_xml_node($root, $doc, 'data', $this->hotSpotData);
    $data_root->appendChild($doc->createTextNode($this->hotSpotDataDetail));
  }

  private function _krpano_detail_titles($field) {
    return $this->detail_messages[$field][$this->lan];
  }

  private function _krpano_detail_info($location) {
    //Calculate GPS coordinates
    $coordinates = $this->_krpano_gmap_to_gps($location['landMark']['latitude'],
                                              $location['landMark']['longitude']);
    //Share info
    global $language;
    if ($language->language == 'en') {
      $share_title = variable_get('cloud360_share_title_en', 'Chech out this amazing page!');
      $share_comment = variable_get('cloud360_share_comment_en', 'Default comment');
    }
    if ($language->language == 'es') {
      $share_title = variable_get('cloud360_share_title_es', 'Revisa esta página!');
      $share_comment = variable_get('cloud360_share_comment_es', 'Comentario');
    }
    $share_url = 'http://'.$_SERVER['SERVER_NAME'].'/'.$language->language.'/image360?pid='.$_GET['pid'];
    $share_image = $location['imageUrl'];

    //Create html
    $return  = '<div class="krpano-title">'.$location['name'].'</div>';
    $return .= '<div class="krpano-wrapper">';
    $return .= '<div class="columns">';
    $return .= '<div class="left-content">';
    $return .= '<div class="title">'.$this->_krpano_detail_titles('information').'</div>';
    $return .= '<div class="logo"><img src="'.$location['logo'] .'" alt="NO LOGO FOUND" /></div>';
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('coordinates'), $coordinates); 
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('alitude'), $location['landMark']['altitude'] . ' msnm');
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('company'), $location['owner']);
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('description'), $location['description']);
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('address'), $location['contact']['address']);
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('phone'), $location['contact']['phone']);
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('fax'), $location['contact']['fax']);
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('facebook'), $location['contact']['facebook']);
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('twitter'), $location['contact']['twitter']);
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('skype'), $location['contact']['skype']);
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('web'), '<a href="javascript:mypopup(\'http://'.$location['contact']['web'].'\');">'.$location['contact']['web'].'</a>');
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('email'), l($location['contact']['email'], 'mailto:'.$location['contact']['email']));
    $return .= $this->_krpano_render_detail_row($this->_krpano_detail_titles('pcredits'), $location['copyright']);
    $return .= '</div>';
    $return .= '<div class="right-content">';
    $return .= '<div class="title share">'.$this->_krpano_detail_titles('share').'</div>';
    $return .= l($this->_krpano_detail_titles('like'), 'like_360', array('query'=>array('uid'=>$location['uid']), 'attributes'=>(array('class'=>'share-link like'))));
    $return .= l($this->_krpano_detail_titles('notLike'), 'notlike_360', array('query'=>array('uid'=>$location['uid']), 'attributes'=>(array('class'=>'share-link notlike'))));
    $return .= l($this->_krpano_detail_titles('favorites'), 'favorites_360', array('query'=>array('uid'=>$location['uid']), 'attributes'=>(array('class'=>'share-link favorites'))));
    $return .= '<div class="social">';
    $return .= '<div class="facebook"><div class="text"><a href="javascript:share_me(\''.$share_title.'\',\''.$share_comment.'\',\''.$share_url.'\', \''.$share_image.'\')">'.$this->_krpano_detail_titles('like').'</a></div></div>';
    $return .= '<div class="tweeter"><div class="text"><a href="javascript:share_me(\''.$share_title.'\',\''.$share_comment.'\',\''.$share_url.'\', \''.$share_image.'\')">'.$this->_krpano_detail_titles('tweet').'</a></div></div>';
    $return .= '</div>';
    $return .= '</div>';
    $return .= '</div>';
    if (_cloud360_get_user_id()) {
      if (_cloud360_favorites_360_validate($this->pid)) {
        $return .= '<div class="user-favorites">';
        $return .= '<div class="title">'.$this->_krpano_detail_titles('favorites_comments').'</div>';
        $return .= '<div class="content">'.$this->_krpano_render_user_favorites($location['uid']).'</div>';
        $return .= '</div>';
      }
    }
    $return .= '<div class="comments">';
    $return .= '<div class="title">'.$this->_krpano_detail_titles('comments').'</div>';
    $return .= '<div class="content">'.$this->_krpano_render_comments($location['uid'], $location['commentsEnabled']).'</div>';
    $return .= '</div>';
    $return .= '</div>';
    return $return;
  }

  private function _krpano_gmap_to_gps($lat, $lng) {
    $result = '';
    $result .= $this->_krpano_clac_coordinate($lat, 'v');
    $result .= ' ';
    $result .= $this->_krpano_clac_coordinate($lng, 'h');
    return $result;
  }

  private function _krpano_clac_coordinate($coordinate, $option) {
    //Calculate Degree
    $component = number_format($coordinate, 0);
    $position;
    if ($component >= 0) {
      $position = 'pos';
    } else {
      $position = 'neg';
    }
    $result = $this->degree_conf[$this->lan][$option][$position].' '.abs($component).'° ';
    //Calculate Minutes
    $minutes = (abs($coordinate) - abs(floor($component))) * 60;
    $result .= abs(number_format($minutes, 0)).'\' ';
    //Calculate Seconds
    $seconds = (abs($minutes) - abs(floor($minutes))) * 60;
    $result .= abs(number_format($seconds, 0)).'\'\'';
    return $result;
  }
  
  private function _krpano_render_detail_row($title, $data) {
    if ($data && $data != '<a href="/"></a>' && $data != '<a href="mailto:"></a>' && $data != '<a href="javascript:mypopup(\'http://\');"></a>' && strlen($data))
      return '<div class="detail"><span class="bold">'.$title.'</span>'.$data.'</div>';
    else
      return '';
  }
  
  private function _krpano_render_comments($uid, $enabled = FALSE) {
    global $user;
    $result = l($this->_krpano_detail_titles('leave_comment'), 'user/login', array('attributes' => array('class' => 'text')));
    //Get Comment Form
    $form = '';
    if($user->uid != 0 && $enabled) {
      $result = '';
      $form = drupal_get_form('cloud360_comment_form', $uid);
    }
    //Get all comments
    $api = 'listComments';
    $postParameters = array('filter' => array('entityId' => $uid,
                                              'pageSize' => 20,
                                                 'start' => 0,),);
    $comments = _cloud360_get_object($api, NULL, $postParameters);
    //Render comments
    foreach($comments['results'] as $comment) {
      $result .= '<div class="comment"><span class="author">User '.$comment['userLogin'].': </span><span class="text">'.$comment['text'].'</span>';
      $result .= _cloud360_denounce_link($uid, $comment['uid']).'</div>';
    }
    //Render
    return $result.drupal_render($form);
  }
  
  private function _krpano_render_user_favorites($lid) {
    $result = '';
    $count = -1;
    //Get user id
    $uid = _cloud360_get_user_id();
    //Get all comments
    $api = 'userListFavoritesComments';
    $postParameters = array('filter' => array('entityId' => $lid,
                                                'userId' => $uid,
                                                 'fType' => 0,),);
    $comments = _cloud360_get_object($api, NULL, $postParameters);
    //Render comments
    if (array_key_exists('favoriteNotes', $comments)) {
      foreach($comments['favoriteNotes'] as $key=>$comment) {
        if($comment != '_') {
          $count += 1;
          $result .= '<div class="comment"><span class="text">'.$comment.'</span>';
          $result .= _cloud360_delete_link($lid, $key).'</div>';
        }
      }
    }
    //Render
    if($count < 3) {
      $form = drupal_get_form('cloud360_user_comment_form', $lid);
    }
    
    return $result.drupal_render($form);
  }
  
  private function _krpano_render_hot_spots(&$root, &$doc) {
    foreach($this->hot_spots as $key=>$spot) {
      //Create infotext
      $this->_krpano_set_infotext($key + 1, $spot);
      //Add infotext
      $this->_krpano_add_xml_node($root, $doc, 'plugin', $this->infotext);
      //Create hotspot
      $this->_krpano_set_hotspot($key + 1, $spot);
      //Add hotspot
      $this->_krpano_add_xml_node($root, $doc, 'hotspot', $this->hotSpot);
      //Create hotspot data and detail
      $this->_krpano_set_hotspot_data($key + 1, $spot);
      //Add data text
      $this->_krpano_add_datatxt($root, $doc);
    }
  }
  
  private function _krpano_set_infotext($key, &$spot) {
    //Name
    $this->infotext['name'] = 'info_text'.$key;
    //Images
    foreach($spot['images'] as $key_image=>$image) {
      $key_image = $key_image + 1;
      $this->infotext['imgurl'.$key_image] = $image;
    }
    //Headtitle
    $this->infotext['headtitle'] = $spot['name'];
  }
  
  private function _krpano_set_hotspot($key, &$spot) {
    //Name
    $this->hotSpot['name'] = 'spot'.$key;
    //click
    $this->hotSpot['onclick'] = 'action(show_info_text,info_text'.$key.',\'data:htmldata'.$key.'\');';
    //location
    $this->hotSpot['ath'] = $spot['ath'];
    $this->hotSpot['atv'] = $spot['atv'];
  }
  
  private function _krpano_set_hotspot_data($key, &$spot) {
    //Set hotspot data name
    $this->hotSpotData['name'] = 'htmldata'.$key;
    //Set hotspot data detail
    $detail  = '<p align="left">' . $spot['description'] . '<br /></p>';
    $detail .= '<p align="left">';
    if ($spot['contact']['web']) {
     $detail .= 'Web: <a href="event:js(mypopup(http://' . $spot['contact']['web'] . ');return false;)">'.$spot['contact']['web'].'</a><br />';
    }
    if ($spot['contact']['email']) {
      $detail .= 'Email: ' . l(t($spot['contact']['email']), 'mailto:' . $spot['contact']['email'], array('absolute'=>TRUE));
    }
    $detail .= '</p>';
    
    $this->hotSpotDataDetail = $detail;
  }
  
  private function _krpano_set_spot(&$root, &$plugin_root, &$doc) {
    foreach($this->map_spots as $spot) {
      //Verify and create the near spots
      if (!file_exists(drupal_get_path('module', 'krpano').'/panoramas/'.$spot['uid'].'.xml') && $this->stop_recursive) {
        $new_spot = new class_krpano($spot['uid'], FALSE);
        $new_spot->krpano_create_xml();
      }
      if($spot['cone']) {
        $this->spot['heading'] = $spot['heading'];
        $this->spot['active'] = true;
      }
      $this->spot['lat'] = $spot['landmark'][0];
      $this->spot['lng'] = $spot['landmark'][1];
      $this->spot['name'] = 's'.$spot['uid'];
      $this->spot['onhover'] = 'showtext(\'' . $spot['title']. '\');';
      if (array_key_exists('categories', $spot)) {
        $this->spot['onclick'] = 'openurl(\'image360?pid=' . $spot['uid'] . '\', _parent) ;';
        $this->spot['url'] = _cloud360_get_category_icon($spot['categories'][0], TRUE);
      }
      else {
        $this->spot['onclick'] = 'showtext(\'' . $spot['title']. '\');';
        $this->spot['url'] = '/' . drupal_get_path('module', 'gmap') . '/markers/clasifiedLocation.png';
      }
      $this->_krpano_add_xml_node($plugin_root, $doc, 'spot', $this->spot);
      //Add spot action
//      $action1 = $root->appendChild($doc->createElement('action'));
//      $action1->setAttribute('name',  $this->spot['name']);
//      $action1->appendChild($doc->createTextNode('plugin[map].activatespot('.$this->spot['name'].'); plugin[map].pantospot('.$this->spot['name'].'); loadpano('.$spot['uid'].'.xml,null,MERGE,BLEND(1));'));
    }
  }
  
  public function valid_data() {
    return $this->valid_data;
  }
}