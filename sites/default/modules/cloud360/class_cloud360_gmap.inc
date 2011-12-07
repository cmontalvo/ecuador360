<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of class_cloud360_gmap
 *
 * @author cesar
 */
class class_cloud360_gmap {
  private $markers = FALSE;
  
  private $map_data = array('id' => 'my-map',
                         'width' => '100%',
                        'height' => '400px',
                      'latitude' => 41.9023,
                     'longitude' => -87.5391,
                          'zoom' => 7,
                       'maptype' => 'Map',
                   'controltype' => 'Small',
                       //'markers' => NULL,
      );

  private $map = array('#type' => 'gmap',
    '#gmap_settings' => '',);

  function  __construct($parameters = NULL, $macro = NULL) {
    //Configure object
    if($macro) {
      $this->map_data = gmap_parse_macro($macro);
    }
    else {
      $this->_cloud360_gmap_map_parameters($parameters);
    }
    $this->map['#gmap_settings'] = $this->map_data;
  }
  
  public function displayMap() {
    drupal_add_js('jQuery(document).ready(function () {
      var categories = \''._cloud360_render_catedories_map().'\';
      mapControls(\'map-wrapper\', jQuery(\'#gmap-map360-gmap0\'), categories);
    });', 'inline');

    return '<div id="map-wrapper" class="map-wrapper">'.drupal_render($this->map).'</div>';
  }

  public function addMarker($type, $uid, $marker, $latitude, $longitude, $title = NULL, $description = NULL) {
    $marker_class = 'photo360';
    //Validate type
    if ($type == 2) {
      $marker = 'clasifiedLocation';
      $marker_class = 'clasified';
    }
    //Validate markers in map
    if(!$this->markers) {
      $this->map_data[] = 'markers';
      $this->markers = TRUE;
    }
    //Validate title value
    if (!$title) {
      $title = 'Add Title';
    }
    //Validate description value
    if (!$description){
      $description = 'Add description';
    }
    //Add text format to title and description
    $text  = '<div class="marker-wrapper ' . $marker_class . '">';
    if($type == 1) {
      $text .= '<div class="marker-title">'.l($title, 'image360', array('query'=>array('pid'=>$uid))).'</div>';
    }
    else {
      $text .= '<div class="marker-title green">' . $title . '</div>';
    }
    $text .= '<div class="marker-description">'.$description.'</div>';
    $text .= '</div>';
    //Add marker
    $this->map['#gmap_settings']['markers'][] = array('options' => '',
                                                    'longitude' => $longitude,
                                                     'latitude' => $latitude,
                                                   'markername' => $marker,
                                                       'offset' => 0,
                                                         'text' => $text,
                                                           );
  }

  private function _cloud360_gmap_map_parameters($parameters) {
    if ($parameters) {
      foreach ($this->map_data as $paramKey => $parameter) {
        foreach($parameters as $key => $value) {
          if ($key == $paramKey) {
            $this->map_data[$paramKey] = $value;
          }
        }
      }
    }
  }
}

