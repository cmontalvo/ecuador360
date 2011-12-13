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
  $loginService = array('Facebook' => 'facebook',
                       'Twitter'  => 'twitter');
  
  $login = $user->name;
  $social = 'ecuador360';
  
  if (array_key_exists('rpx', $_SESSION)) {
    $social = $loginService[$_SESSION['rpx']['profile']['providerName']];
    if ($social == 'facebook') {
      $login = $_SESSION['rpx']['profile']['email'];
    }
    else {
      $login = end(explode('/', $_SESSION['rpx']['profile']['url']));
    }
  }
    
  $api = 'userLogin';
  $postParameters = array('filter' => array('login' => $login,
                                           'social' => $social));
  
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