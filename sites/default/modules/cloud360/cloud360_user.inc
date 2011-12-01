<?php
/*
 * Function to execute on user login form
 */
function _cloud360_user_login($form, &$form_state) {
  _cloud360_set_user_id();
  _cloud360_get_favorites();
}
/*
 * Function to save the cloud user id on session
 */
function _cloud360_set_user_id() {
  global $user;
  
  $api = 'userLogin';
  $postParameters = array('filter' => array('login' => $user->mail,
                                           'social' => 'WEB'));
  
  $result = _cloud360_get_object($api, NULL, $postParameters);
  
  $_SESSION['cloud360_user_id'] = $result['userId'];
}
/*
 * function to get the cloud user id from sexxion
 */
function _cloud360_get_user_id() {
  $_SESSION['cloud360_user_id'] = FALSE;
  global $user;
  if($user->uid != 0) {
    if(!$_SESSION['cloud360_user_id']) {
      _cloud360_set_user_id();
    }
  }
  
  return $_SESSION['cloud360_user_id'];
}