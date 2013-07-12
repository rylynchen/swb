<?php

/**
 * Sinaweibo bind view page.
 *
 * @param $account
 */
function swb_page($account) {
	$account_wrapper = entity_metadata_wrapper('user', $account);
	if ($account_wrapper->field_swb_bind->value()) {
		$msg = t('已绑定新浪微博账号 <b> %name </b>。', array('%name' => $account_wrapper->field_swb_name->value()));
		$status = 'status';
		$html = l(t('重新绑定'), 'user/'.$account->uid.'/swb/bind/redirect');
		$html .= '&nbsp;&nbsp;&nbsp;&nbsp;';
		$html .= l(t('取消绑定'), 'user/'.$account->uid.'/swb/delete');
	}
	else {
		$settings = swb_settings();
		$msg = t('还未绑定新浪微博账号');
		$status = 'warning';
	  $html = l(theme('image', array('path' => 'http://www.sinaimg.cn/blog/developer/wiki/240.png', 'alt' => t('绑定新浪微博账号'))), 'user/'.$account->uid.'/swb/bind/redirect', array('html' => TRUE));
	}
	drupal_set_message($msg, $status);
	return $html;
}

/**
 * Confirm form for deleting a sina weibo bind.
 */
function swb_delete_confirm_form($form, &$form_state, $account) {
  $form_state += array('account' => $account);
  $account_wrapper = entity_metadata_wrapper('user', $account);
  $confirm_question = t('确定要取消微博账号 <b>%name</b> 的绑定 ?', array('%name' => $account_wrapper->field_swb_name->value()));
  return confirm_form($form, $confirm_question, 'user/'.$account->uid.'/swb');
}

/**
 * Sina weibo bind delete confirm form submit handler.
 */
function swb_delete_confirm_form_submit($form, &$form_state) {
  $account = $form_state['account'];
  $account_wrapper = entity_metadata_wrapper('user', $account);
  $account_wrapper->field_swb_bind->set(0);
  $account_wrapper->field_swb_name->set('');
  $account_wrapper->field_swb_uid->set('');
  $account_wrapper->field_swb_oauth_token->set('');
  $account_wrapper->save();
  drupal_set_message(t('已取消微博账号绑定'));
  $form_state['redirect'] = 'user/'.$account->uid.'/swb';
}