<?php
/*
 * Define Comment Form
 */
function cloud360_comment_form($form, &$form_state, $uid) {
  global $language;
  $text = array('en' => 'Comment',
                'es' => 'Comentario');
  
  $text_boutton = array('en' => 'Submit',
                        'es' => 'Enviar');
  //Location ID
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $uid,
  );
  //Comment Field
  $form['comment'] = array(
    '#type' => 'textfield',
    '#title' => $text[$language->language],
    '#multiple' => FALSE,
    '#required' => TRUE,
  );
  //Submit Buttom
  $form['submit'] = array(
    '#id' => 'comment-form-submit',
    '#type' => 'submit',
    '#value' => t($text_boutton[$language->language]),
  );
  //Retutm form
  return $form;
}

function cloud360_comment_form_submit($form, &$form_state) {
  //Get all comments
  $api = 'userAddComment';
  $postParameters = array('filter' => array('entityId' => $form['uid']['#value'],
                                              'userId' => _cloud360_get_user_id(),
                                                'text' => $form['comment']['#value'],),);
  $comment = _cloud360_get_object($api, NULL, $postParameters);
  
  drupal_goto('image360', array('query'=>array('pid'=>$form['uid']['#value'])));
}
/*
 * Define User Favorite Comment Form
 */
function cloud360_user_comment_form($form, &$form_state, $uid) {
  global $language;
  $text = array('en' => 'Favorite Comment',
                'es' => 'Comentario Favorito');
  
  $text_boutton = array('en' => 'Submit',
                        'es' => 'Enviar');
  //Location ID
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $uid,
  );
  //Comment Field
  $form['comment'] = array(
    '#type' => 'textfield',
    '#title' => $text[$language->language],
    '#multiple' => FALSE,
    '#required' => TRUE,
  );
  //Submit Buttom
  $form['submit'] = array(
    '#id' => 'user-comment-form-submit',
    '#type' => 'submit',
    '#value' => t($text_boutton[$language->language]),
  );
  //Retutm form
  return $form;
}

function cloud360_user_comment_form_submit($form, &$form_state) {
  //Get all comments
  $api = 'userAddFavoritesComment';
  $postParameters = array('filter' => array('entityId' => $form['uid']['#value'],
                                              'userId' => _cloud360_get_user_id(),
                                               'fType' => 0,
                                                'text' => $form['comment']['#value'],),);
  $comment = _cloud360_get_object($api, NULL, $postParameters);
  
  drupal_goto('image360', array('query'=>array('pid'=>$form['uid']['#value'])));
}



///*
// * Define activity form
// */
//function cloud360_activity_form($form, &$form_state) {
//  //Activity Name Spanish
//  $form['name_es'] = array(
//    '#type' => 'textfield',
//    '#title' => 'Nombre Actividad',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//  );
//  //Activity Name English
//  $form['name_en'] = array(
//    '#type' => 'textfield',
//    '#title' => 'Activity Name',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//  );
//  //Submit Button
//  $form['submit'] = array(
//    '#type' => 'submit',
//    '#value' => t('Submit'),
//  );
//  //Return form
//  return $form;
//}
////location360 form validate
//function cloud360_activity_form_validate($form, &$form_state) {
//
//}
////location360 form submit
//function cloud360_activity_form_submit($form, &$form_state) {
//  //Save Activity
//  $post = array('filter'=> array(
//                          'localizedNames' => array( 0 => array('lang' => 'en_US', 'value' => $form_state['values']['name_en']),
//                                                     1 => array('lang' => 'es_ES', 'value' => $form_state['values']['name_es']),),
//                                     'uid' => 0));
//  $result = _cloud360_get_object('addActivity', NULL, $post);
//}
///*
// * Define region form
// */
//function cloud360_region_form($form, &$form_state) {
//  //Region Name Spanish
//  $form['name_es'] = array(
//    '#type' => 'textfield',
//    '#title' => 'Nombre Región',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//  );
//  //Region Name English
//  $form['name_en'] = array(
//    '#type' => 'textfield',
//    '#title' => 'Region Name',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//  );
//  //Submit Button
//  $form['submit'] = array(
//    '#type' => 'submit',
//    '#value' => t('Submit'),
//  );
//  //Return form
//  return $form;
//}
////location360 form validate
//function cloud360_region_form_validate($form, &$form_state) {
//
//}
////location360 form submit
//function cloud360_region_form_submit($form, &$form_state) {
//
//}
///*
// * Define category form
// */
//function cloud360_category_form($form, &$form_state) {
//  //Name Wrapper
//  $form['group_name'] = array(
//    '#type' => 'fieldset',
//    '#title' => 'Category Name',
//    '#collapsed' => FALSE,
//    '#collapsible' => TRUE,
//  );
//  //Category Name Spanish
//  $form['group_name']['name_es'] = array(
//    '#type' => 'textfield',
//    '#title' => 'Nombre Categoría',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//  );
//  //Category Name English
//  $form['group_name']['name_en'] = array(
//    '#type' => 'textfield',
//    '#title' => 'Category Name',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//  );
//  //Detail Wrapper
//  $form['group_detail'] = array(
//    '#type' => 'fieldset',
//    '#title' => 'Category Name',
//    '#collapsed' => FALSE,
//    '#collapsible' => TRUE,
//  );
//  //Category Preview Web
//  $form['group_detail']['preview_web'] = array(
//    '#type' => 'managed_file',
//    '#title' => 'Preview Web Page Image',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//    //'#upload_location' => 'public://category_images/',
//    '#upload_location' => 'public://category_images/',
//  );
//  //Category Preview Mobile
//  $form['group_detail']['preview_mobile'] = array(
//    '#type' => 'managed_file',
//    '#title' => 'Preview Mobile Image',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//    '#upload_location' => 'public://category_images/',
//  );
//  //Category Icon
//  $form['group_detail']['icon'] = array(
//    '#type' => 'managed_file',
//    '#title' => 'Icon Image',
//    '#multiple' => FALSE,
//    '#required' => TRUE,
//    '#upload_location' => 'public://category_images/',
//  );
//  //Submit Button
//  $form['submit'] = array(
//    '#type' => 'submit',
//    '#value' => t('Submit'),
//  );
//  //Return form
//  return $form;
//}
////location360 form validate
//function cloud360_category_form_validate($form, &$form_state) {
//
//}
////location360 form submit
//function cloud360_category_form_submit($form, &$form_state) {
//  //Save Preview Web Image
//  $file = file_load($form_state['values']['preview_web']);
//  $post = array('filter'=> array('file' => '@'.drupal_realpath($file->uri),));
//  $preview_web = _cloud360_get_object('uploadFile', NULL, $post);
//  //Save Preview Mobile Image
//  $file = file_load($form_state['values']['preview_mobile']);
//  $post = array('filter'=> array('file' => '@'.drupal_realpath($file->uri),));
//  $preview_mobile = _cloud360_get_object('uploadFile', NULL, $post);
//  //Save Icon
//  $file = file_load($form_state['values']['preview_web']);
//  $post = array('filter'=> array('file' => '@'.drupal_realpath($file->uri),));
//  $icon = _cloud360_get_object('uploadFile', NULL, $post);
//
//  //Save Category
//  $post = array('filter'=> array('iconUrl' => $preview_web,
//                                'imageUrl' => $icon,
//                          'localizedNames' => array( 0 => array('lang' => 'en_US', 'value' => $form_state['values']['name_en']),
//                                                     1 => array('lang' => 'es_ES', 'value' => $form_state['values']['name_es']),),
//                                     'uid' => 0));
//  $result = _cloud360_get_object('addCategory', NULL, $post);
//}
///*
// * Define location360 form
// */
//function cloud360_location360_form($form, &$form_state) {
//  //Activities field
//  $form['activities'] = array(
//    '#type' => 'select',
//    '#title' => 'Activities',
//    '#multiple' => TRUE,
//    '#options' => array('asd' => 'asd',
//                    'asertwe' => 'vaga'),
//  );
//  //Categories field
//  $form['categories'] = array(
//    '#type' => 'select',
//    '#title' => 'Categories',
//    '#multiple' => TRUE,
//    '#options' => array('asd' => 'asd',
//                    'asertwe' => 'vaga'),
//  );
//  //Contact Info Wrapper
//  $form['group_contact'] = array(
//    '#type' => 'fieldset',
//    '#title' => 'Contact Information',
//    '#collapsed' => TRUE,
//    '#collapsible' => TRUE,
//  );
//
//  $form['group_contact']['address'] = array(
//    '#type' => 'textfield',
//    '#title' => 'Address',
//  );
//
//  $form['submit'] = array(
//    '#type' => 'submit',
//    '#value' => t('Submit'),
//  );
//
//  return $form;
//}
////location360 form validate
//function cloud360_location360_form_validate($form, &$form_state) {
//
//}
////location360 form submit
//function cloud360_location360_form_submit($form, &$form_state) {
//
//}