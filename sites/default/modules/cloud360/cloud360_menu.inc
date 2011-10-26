<?php
///*
// * Function to create Cloud 360 Menu
// */
//function _cloud360_build_menu(&$items) {
//  //Admin Page
//  $items['admin/cloud360'] = array(
//    'title' => t('Cloud360 Admin'),
//    'description' => 'Cloud360 Custom Module',
//    'page callback' => '_cloud360_admin',
//    'access callback' => TRUE,
//    'file' => 'cloud360_menu.inc',
//    'menu_name' => 'cloud360',
//  );
//  //Admin Activities Page
//  $items['admin/cloud360/activity'] = array(
//      'title' => 'Activities Admin Page',
//      'description' => t('Page to administer Activities'),
//      'page callback' => '_cloud360_activity_admin',
//      'access arguments' => array('access content'),
//      'file' => 'cloud360_menu.inc',
//      'parent' => 'admin/cloud360',
//  );
//  //Admin Regions Page
//  $items['admin/cloud360/region'] = array(
//      'title' => 'Regions Admin Page',
//      'description' => t('Page to administer Regions'),
//      'page callback' => '_cloud360_region_admin',
//      'access arguments' => array('access content'),
//      'file' => 'cloud360_menu.inc',
//      'parent' => 'admin/cloud360',
//  );
//  //Admin Categories Page
//  $items['admin/cloud360/category'] = array(
//      'title' => 'Regions Admin Page',
//      'description' => t('Page to administer Categories'),
//      'page callback' => '_cloud360_category_admin',
//      'access arguments' => array('access content'),
//      'file' => 'cloud360_menu.inc',
//      'parent' => 'admin/cloud360',
//  );
//  //Admin Location Page
//  $items['admin/cloud360/location'] = array(
//      'title' => '360 Location Admin Page',
//      'description' => t('Page to administer 360 Location'),
//      'page callback' => '_cloud360_location360_admin',
//      'access arguments' => array('access content'),
//      'file' => 'cloud360_menu.inc',
//      'parent' => 'admin/cloud360',
//  );
//
//  return $items;
//}
//
////Callback of cloud360 admin page
//function _cloud360_admin() {
////  $menu = menu_get_item('admin/cloud360');
////  $menu2 = menu_build_tree('cloud360');
//  $menu3 = menu_tree('cloud360');
//  krumo($menu3);
////  $menu4 = menu_tree_data($menu2);
//  krumo(menu_tree_all_data('cloud360'));
//  return '<div class="cloud360-admin-wrapper">hola'.drupal_render(menu_tree('cloud360')).'</div>';
//}
//
////Callback to administer activities
//function _cloud360_activity_admin() {
//  return drupal_get_form('cloud360_activity_form');
//}
//
////Callback to administer regions
//function _cloud360_region_admin() {
//  return drupal_get_form('cloud360_region_form');
//}
//
////Callback to administer categories
//function _cloud360_category_admin() {
//  return drupal_get_form('cloud360_category_form');
//}
//
////Callback to administer 360 locations
//function _cloud360_location360_admin() {
//  return drupal_get_form('cloud360_location360_form');
//}