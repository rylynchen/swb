<?php

/**
 * Sina Weibo settings form.
 */
function swb_settings_form() {
	$settings = swb_settings();
	$form = array();
	$form['info'] = array(
		'#markup' => t('You can get key and secret form ').l(t('open.weibo.com'), 'http://open.weibo.com/', array('external' => TRUE, 'attributes' => array('target' => '_blank'))),
	);
	$form['key'] = array(
		'#type' => 'textfield',
		'#title' => t('Key'),
		'#default_value' => $settings->key,
		'#required' => TRUE,
	);
	$form['secret'] = array(
		'#type' => 'textfield',
		'#title' => t('Secret'),
		'#default_value' => $settings->secret,
		'#required' => TRUE,
	);
	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);
	$form['#submit'][] = 'swb_settings_form_submit';
	return $form;
}

/**
 * Sina Weibo settings form submit handler.
 */
function swb_settings_form_submit($form, &$form_state) {
	$settings = new stdClass();
	$settings->key = trim($form_state['values']['key']);
	$settings->secret = trim($form_state['values']['secret']);
	variable_set('swb_settings', serialize($settings));
	drupal_set_message(t('Your configuration have been saved.'));
}