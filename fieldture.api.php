<?php

/**
 * Provide component information.
 *
 * @return array
 */
function hook_fieldture_info() {
  return array(
    'my_component_name' => array(
      'label' => 'Component label',
      'field' => array(), // Optionnal if no field is required.
      'instance' => array(), // Optionnal if no field is required.
    ),
  );
}

/**
 * Alter fieldture information.
 *
 * @param $info
 */
function hook_fieldture_info_alter(&$info) {
}
