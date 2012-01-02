<?php
/**
 * Description of class_colud360
 *
 * @author cesar
 */
class class_cloud360_service_data {
  //private $url = 'https://webcaptur.dyndns.org/';
  private $url = 'https://ec360-webservices-1645451952.us-east-1.elb.amazonaws.com/captur-webservices-0.1/';

  private $server_image_path = '';

  //private $secKey = 'd617345f-4fe2-402d-8e3b-305c07a3368e';
  private $secKey = '6ccddd3a-3acb-4c4a-a147-70ecb24b162b';

  private $default_big_image = 'sites/default/files/no_image_big.jpg';

  private $default_small_image = 'sites/default/files/no_image_small.png';

  private $curl_get_options = array(CURLOPT_URL => '',
                                 CURLOPT_HEADER => 0,
                         CURLOPT_RETURNTRANSFER => TRUE,
                                //CURLOPT_TIMEOUT => 4,
                         CURLOPT_SSL_VERIFYPEER => FALSE );

  private $curl_post_options = array(CURLOPT_URL => '',
                                  CURLOPT_HEADER => 0,
                          CURLOPT_RETURNTRANSFER => TRUE,
                                  //CURLOPT_TIMEOUT => 4,
                          CURLOPT_SSL_VERIFYPEER => FALSE,
                                    CURLOPT_POST => TRUE,
                              CURLOPT_POSTFIELDS => '',
                              CURLOPT_HTTPHEADER => array('Content-Type: application/json',),
                          //CURLOPT_FOLLOWLOCATION => 1,
                          // CURLOPT_FRESH_CONNECT => 1,
                            //CURLOPT_FORBID_REUSE => 1
                            );

  private $curl_post_options_file = array(CURLOPT_URL => '',
                                       CURLOPT_HEADER => 0,
                               CURLOPT_RETURNTRANSFER => TRUE,
                                      //CURLOPT_TIMEOUT => 4,
                               CURLOPT_SSL_VERIFYPEER => FALSE,
                                         CURLOPT_POST => TRUE,
                                   CURLOPT_POSTFIELDS => '',
                                   CURLOPT_HTTPHEADER => array('Content-Type: multipart/mixed',),
                          //CURLOPT_FOLLOWLOCATION => 1,
                          // CURLOPT_FRESH_CONNECT => 1,
                            //CURLOPT_FORBID_REUSE => 1
                            );
  
  private $languageServices = array('es' => 'es_ES',
                                    'en' => 'en_US');
  
  private $apiDef = array(   'getConfig' => array('apiUrl' => 'api/configuration/startup',
                                                  'method' => 'GET',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'loc' => ''),),),
               'getPanoramicPhotography' => array('apiUrl' => 'api/view/panoramicPhotography',
                                                  'method' => 'POST',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'uid' => '',
                                                                                     'loc' => ''), ),
                                          'postParameters' => array('filter' => array('client' => 'WEB',
                                                                                         'uid' => ''), ), ),
                'getPhotographyLocation' => array('apiUrl' => 'api/view/photographyLocation',
                                                  'method' => 'POST',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'uid' => '',
                                                                                     'loc' => ''),),
                                          'postParameters' => array('filter' => array('client' => 'WEB',
                                                                                         'uid' => ''), ), ),
                 'getClassifiedLocation' => array('apiUrl' => 'api/view/classifiedLocation',
                                                  'method' => 'POST',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'uid' => '',
                                                                                     'loc' => ''),),
                                          'postParameters' => array('filter' => array('client' => 'WEB',
                                                                                         'uid' => ''), ), ),
                         'getActivities' => array('apiUrl' => 'api/info/activityList',
                                                  'method' => 'GET',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'loc' => ''),),),
                         'getCategories' => array('apiUrl' => 'api/info/categoryList',
                                                  'method' => 'POST',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'loc' => ''),),
                                          'postParameters' => array('filter' => array('client' => 'WEB', ), ), ),
                            'getRegions' => array('apiUrl' => 'api/info/regionList',
                                                  'method' => 'GET',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'loc' => ''),),),
                           'getLandmark' => array('apiUrl' => 'api/search/landmark',
                                                  'method' => 'POST',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'loc' => ''),),
                                          'postParameters' => array('filter' => array('categories' => '',
                                                                                        'landmark' => '',
                                                                                         'radious' => '',
                                                                                          'zlevel' => ''),),),
                         'searchGeneral' => array('apiUrl' => 'api/search/general',
                                                  'method' => 'POST',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'loc' => ''),),
                                          'postParameters' => array('filter' => array('categories' => '',
                                                                                        'pageSize' => '',
                                                                                           'start' => '',
                                                                                            'term' => ''),),),
                            'searchRank' => array('apiUrl' => 'api/search/rank',
                                                  'method' => 'POST',
                                                   'param' => array('query' => array('key' => '',
                                                                                     'loc' => ''),),
                                          'postParameters' => array('filter' => array('categories' => '',
                                                                                        'pageSize' => '',
                                                                                           'start' => '',),),),

                            'uploadFile' => array('apiUrl' => 'api/adm/postsSample2',
                                                  'method' => 'POSTFile',
                                                   'param' => array('query' => array('key' => '',),
                                                       ),
                                          'postParameters' => array('filter' => array('file' => '',),),),

                            'addActivity' => array('apiUrl' => 'api/adm/addActivity',
                                                   'method' => 'POST',
                                                   'param' => array('query' => array('key' => '', ), ),
                                          'postParameters' => array('filter' => array(
                                              'localizedNames' => array( 0 => array('lang' => '', 'value' => ''),
                                                                         1 => array('lang' => '', 'value' => '')),
                                                         'uid' => ''),),),

                            'addCategory' => array('apiUrl' => 'api/adm/addCategory',
                                                   'method' => 'POST',
                                                   'param' => array('query' => array('key' => '',),
                                                       ),
                                          'postParameters' => array('filter' => array('iconUrl' => '',
                                                                                     'imageUrl' => '',
                                                                               'localizedNames' => array( 0 => array('lang' => '', 'value' => ''),
                                                                                                          1 => array('lang' => '', 'value' => '')),
                                                                                          'uid' => ''),),),

                              'userLogin' => array('apiUrl' => 'api/user/getProfile',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                          'postParameters' => array('filter' => array('login' => '',
                                                                                     'social' => '',),),),
      
                          'userFavorites' => array('apiUrl' => 'api/user/plocations',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('categories' => '',
                                                                                         'pageSize' => '',
                                                                                            'start' => '',
                                                                                           'userId' => '',
                                                                                           'client' => '',),),),

                       'userAddFavorites' => array('apiUrl' => 'api/user/addFavorite',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('entityId' => '',
                                                                                         'userId' => '',
                                                                                          'fType' => '',),),),
      
                'userAddFavoritesComment' => array('apiUrl' => 'api/user/addFavoriteNote',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('entityId' => '',
                                                                                         'userId' => '',
                                                                                          'fType' => '',
                                                                                           'text' => ''),),),
      
             'userDeleteFavoritesComment' => array('apiUrl' => 'api/user/deleteFavoriteNote',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('entityId' => '',
                                                                                         'userId' => '',
                                                                                          'fType' => '',
                                                                                         'noteId' => ''),),),
      
              'userListFavoritesComments' => array('apiUrl' => 'api/user/listFavoriteNotes',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('entityId' => '',
                                                                                         'userId' => '',
                                                                                          'fType' => '',),),),
      
                               'userVote' => array('apiUrl' => 'api/user/vote',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('vote' => '',
                                                                                     'userId' => '',
                                                                                   'entityId' => '',),),),
      
                           'listComments' => array('apiUrl' => 'api/user/listComments',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('entityId' => '',
                                                                                       'pageSize' => '',
                                                                                          'start' => '',),),),
      
                         'userAddComment' => array('apiUrl' => 'api/user/addComment',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('entityId' => '',
                                                                                         'userId' => '',
                                                                                           'text' => '',),),),
      
                    'userDenounceComment' => array('apiUrl' => 'api/user/denounceComment',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('text' => '',
                                                                                     'userId' => '',
                                                                                   'entityId' => '',
                                                                                  'commentId' => ''),),),
      
                       'visitPhotography' => array('apiUrl' => 'api/view/visitWeb',
                                                   'method' => 'POST',
                                                    'param' => array('query' => array('key' => '',
                                                                                      'loc' => ''),),
                                           'postParameters' => array('filter' => array('uid' => '',),),),
                         );

  private $api_loaded;

  function __construct($api, $param = NULL, $postParameters = NULL) {
    //Set Image server Path
    $this->server_image_path = variable_get('cloud360_imagesUrl').'/';
    //Set loaded api
    $this->api_loaded = $api;
    //Map paremeters
    $this->_class_cloud360_service_map_parameters('param', 'query', $param);
    //map post parametes
    if ($postParameters) {
      $this->_class_cloud360_service_map_parameters('postParameters', 'filter', $postParameters);
    }
  }
  
  public function getApiData() {
    //Validate service method and add post values
    switch ($this->apiDef[$this -> api_loaded]['method']) {
      case 'GET':
        $response = $this->_class_cloud360_service_curl_get();
        break;
      case 'POST':
        $response = $this->_class_cloud360_service_curl_post();
        break;
      case 'POSTFile':
        $response = $this->_class_cloud360_service_curl_post_file();
        break;
    }

    if (drupal_json_decode($response)) {
      $response = drupal_json_decode($response);
      $this->_class_colud360_service_data_set_image_path($response);
      return $response;
    }
    else {
      return $response;
    }
  }

  private function _class_colud360_service_data_getApiUrl() {
    //Recober api info
    $api = (object) $this->apiDef[$this -> api_loaded];
    //Recober service url
    $apiUrl = $this->url.$api->apiUrl;
    
    return url($apiUrl, $api->param);
  }

  private function _class_colud360_service_data_getLanguage() {
    global $language;
    return $language->language;
  }

  private function _class_cloud360_service_map_parameters($parameterType, $parameterGroup, $parameters) {
    //Configure default parameters
    if($parameterGroup == 'query') {
      $this->apiDef[$this -> api_loaded][$parameterType][$parameterGroup]['key'] = $this->secKey;
      $this->apiDef[$this -> api_loaded][$parameterType][$parameterGroup]['loc'] = $this->languageServices[$this->_class_colud360_service_data_getLanguage()];
    }
    if ($parameters) {
      foreach ($this->apiDef[$this -> api_loaded][$parameterType][$parameterGroup] as $paramKey=>$parameter) {
        foreach($parameters[$parameterGroup] as $key => $value) {
          if ($key == $paramKey) {
            $this->apiDef[$this -> api_loaded][$parameterType][$parameterGroup][$paramKey] = $value;
          }
        }
    }
    }
  }

  private function _class_colud360_service_data_set_image_path(&$response) {
    switch ($this->api_loaded) {
      case 'getCategories':
        $this->_class_cloud360_service_validate_category($response);
        break;
      case 'getPhotographyLocation':
        $this->_class_cloud360_service_validate_photography_location($response);
        break;
      case 'getPanoramicPhotography':
        $this->_class_cloud360_service_validate_panoramic_photography($response);
        break;
      case 'userFavorites':
        foreach($response['results'] as $key=>$result) {
          $this->_class_cloud360_service_validate_photography_location($response['results'][$key]);
        }
        break;
    }
  }

  private function _class_cloud360_service_validate_category(&$response) {
    foreach ($response as $key => $value) {
      if(array_key_exists('imageUrl', $value)) {
        $response[$key]['imageUrl'] = $this->server_image_path.$response[$key]['imageUrl'];
      }
      else {
        $response[$key]['imageUrl'] = $this->default_big_image;
      }
      if(array_key_exists('iconUrl', $value)) {
        $response[$key]['iconName'] = $response[$key]['iconUrl'];
        $response[$key]['iconUrl'] = $this->server_image_path.$response[$key]['iconUrl'];
      }
      else {
        $response[$key]['iconName'] = 'no_image_small.png';
        $response[$key]['iconUrl'] = $this->default_small_image;
      }
    }
  }

  private function _class_cloud360_service_validate_photography_location(&$response) {
    if(array_key_exists('imageUrl', $response)) {
      $response['imageUrl'] = $this->server_image_path.$response['imageUrl'];
    }
    else {
      $response['imageUrl'] = $this->default_big_image;
    }
    if(array_key_exists('logo', $response)) {
      $response['logo'] = $this->server_image_path.$response['logo'];
    }
    else {
      $response['logo'] = $this->default_big_image;
    }
  }

  private function _class_cloud360_service_validate_panoramic_photography(&$response) {
    if(array_key_exists('images', $response)) {
      foreach ($response['images'] as $key => $value) {
        $response['images'][$key] = $this->server_image_path.$value;
      }
    }
    else {
      drupal_set_message($response);
      drupal_goto('cloud360/error');
    }
    //Hotspot images
    foreach($response['hotspots'] as $key=>$value) {
      foreach($value['images'] as $key_image=>$image) {
        $response['hotspots'][$key]['images'][$key_image] = $this->server_image_path.$image;
      }
    }
  }

  private function _class_cloud360_service_curl_get() {
    //Build url
    $url = $this->_class_colud360_service_data_getApiUrl();
    //Set url in curl options
    $this->curl_get_options[CURLOPT_URL] = $url;
    //Execute curl
    $ch = curl_init();
    curl_setopt_array($ch, $this->curl_get_options);
    if( ! $result = curl_exec($ch))
    {
        trigger_error(curl_error($ch));
    }
    curl_close($ch);
    return $result;
  }

  private function _class_cloud360_service_curl_post() {
    //Build url
    $url = $this->_class_colud360_service_data_getApiUrl();
//krumo($url);
    //Recover post parameters
    $post = drupal_json_encode($this->apiDef[$this -> api_loaded]['postParameters']['filter']);
//krumo($post);
    //Set curl options
    $this->curl_post_options[CURLOPT_URL] = $url;
    $this->curl_post_options[CURLOPT_POSTFIELDS] = $post;
    //Execute curl
    $ch = curl_init();
    curl_setopt_array($ch, $this->curl_post_options);

    if(!$result = curl_exec($ch))
    {
      $err = curl_error($ch);
      trigger_error(curl_error($ch));
    }
    curl_close($ch);
//krumo($result);
    return $result;
  }

  private function _class_cloud360_service_curl_post_file()  {
    //Build url
    $url = $this->_class_colud360_service_data_getApiUrl();
    //Recover post parameters
    $post = $this->apiDef[$this -> api_loaded]['postParameters']['filter'];
    //Set curl options
    $this->curl_post_options_file[CURLOPT_URL] = $url;
    $this->curl_post_options_file[CURLOPT_POSTFIELDS] = $post;
    //Execute curl
    $ch = curl_init();
    curl_setopt_array($ch, $this->curl_post_options_file);
    if(!$result = curl_exec($ch))
    {
      $err = curl_error($ch);
      trigger_error(curl_error($ch));
    }
    curl_close($ch);

    return $result;
  }
}