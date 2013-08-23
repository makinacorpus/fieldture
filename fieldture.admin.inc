<?php

/**
 * @file
 *  Administration pages
 */

/**
 * Form helper to anage components on bundles
 *
 * @param string $component
 * @param string $field_name
 *
 * @return array
 */
function fieldture_settings_form($form, $form_state, $component) {
  $info = entity_get_info();
  $options = array();
  foreach ($info as $entity_type => $entity_info) {
    foreach ($entity_info['bundles'] as $bundle => $bundle_info) {
      $options[$entity_info['label']]["$entity_type:$bundle"] = $bundle_info['label'];
    }
  }

  $form['component_name'] = array(
    '#type' => 'value',
    '#value' => $component,
  );

  $form['bundles'] = array(
    '#title' => t("Enable component for these bundles"),
    '#type' => 'select',
    '#options' => $options,
    '#multiple' => TRUE,
    '#size' => count($options, COUNT_RECURSIVE),
    '#default_value' => variable_get($component . '_bundles'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration')
  );

  return $form;
}

/**
 * Form submit for helper form
 *
 * @param $form
 * @param $form_state
 */
function fieldture_settings_form_submit(&$form, $form_state) {
  $enabled = $form_state['values']['bundles'];

  // Get component info.
  $component = $form['component_name']['#value'];
  $info = fieldture_get_info($component);
  if (!empty($info['field'])) {
    // Get bundles to add or remove.
    $old = variable_get($component . '_bundles', array());
    $add = array_diff($enabled, $old);
    $del = array_diff($old, $enabled);

    fieldture_attach_field($component, $add);
    fieldture_detach_field($component, $del);
  }
  variable_set($component . '_bundles', $enabled);

  cache_clear_all('*', 'cache_field', TRUE);
  entity_info_cache_clear();
}
