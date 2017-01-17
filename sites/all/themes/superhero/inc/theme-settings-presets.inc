<?php

/**
 * Add colour settings to superhero framework
 */
function superhero_theme_settings_preset(&$form,&$form_state) {
	$presets = (theme_get_setting('superhero_presets'))?theme_get_setting('superhero_presets'):'W3sibmFtZSI6IlByZXNldCAxIiwic3VwZXJoZXJvX2NvbG9yX2xpbmsiOiIjMDBjNGFhIiwic3VwZXJoZXJvX2NvbG9yX3RleHQiOiIjOTk5OTk5Iiwic3VwZXJoZXJvX2NvbG9yX2hvdmVyIjoiIzAwNWU1MiIsInN1cGVyaGVyb19jb2xvcl9oZWFkaW5nIjoiIzY2NjY2NiJ9LHsibmFtZSI6IlByZXNldCAyIiwic3VwZXJoZXJvX2NvbG9yX2xpbmsiOiIjZWZiYjhlIiwic3VwZXJoZXJvX2NvbG9yX3RleHQiOiIjOTk5OTk5Iiwic3VwZXJoZXJvX2NvbG9yX2hvdmVyIjoiI2UyODUzNSIsInN1cGVyaGVyb19jb2xvcl9oZWFkaW5nIjoiIzY2NjY2NiJ9LHsibmFtZSI6InByZXNldDMiLCJzdXBlcmhlcm9fY29sb3JfdGV4dCI6IiM5OTk5OTkiLCJzdXBlcmhlcm9fY29sb3JfbGluayI6IiNkYjQwM2MiLCJzdXBlcmhlcm9fY29sb3JfaG92ZXIiOiIjOTUxZjFjIiwic3VwZXJoZXJvX2NvbG9yX2hlYWRpbmciOiIjNjY2NjY2In0seyJzdXBlcmhlcm9fY29sb3JfdGV4dCI6IiM5OTk5OTkiLCJzdXBlcmhlcm9fY29sb3JfbGluayI6IiNmNjYzOGIiLCJzdXBlcmhlcm9fY29sb3JfaG92ZXIiOiIjZTYwZDQ4Iiwic3VwZXJoZXJvX2NvbG9yX2hlYWRpbmciOiIjNjY2NjY2In0seyJzdXBlcmhlcm9fY29sb3JfdGV4dCI6IiM5OTk5OTkiLCJzdXBlcmhlcm9fY29sb3JfbGluayI6IiMwMGI0NGUiLCJzdXBlcmhlcm9fY29sb3JfaG92ZXIiOiIjMDA0ZTIyIiwic3VwZXJoZXJvX2NvbG9yX2hlYWRpbmciOiIjNjY2NjY2In0seyJzdXBlcmhlcm9fY29sb3JfdGV4dCI6IiM5OTk5OTkiLCJzdXBlcmhlcm9fY29sb3JfbGluayI6IiM1YWFkZGQiLCJzdXBlcmhlcm9fY29sb3JfaG92ZXIiOiIjMjQ3YmFkIiwic3VwZXJoZXJvX2NvbG9yX2hlYWRpbmciOiIjNjY2NjY2In0seyJzdXBlcmhlcm9fY29sb3JfdGV4dCI6IiM5OTk5OTkiLCJzdXBlcmhlcm9fY29sb3JfbGluayI6IiMxMGQzZmYiLCJzdXBlcmhlcm9fY29sb3JfaG92ZXIiOiIjMDA4YWE5Iiwic3VwZXJoZXJvX2NvbG9yX2hlYWRpbmciOiIjNjY2NjY2In0seyJzdXBlcmhlcm9fY29sb3JfdGV4dCI6IiM5OTk5OTkiLCJzdXBlcmhlcm9fY29sb3JfbGluayI6IiM5NDJlOGYiLCJzdXBlcmhlcm9fY29sb3JfaG92ZXIiOiIjNDYxNjQ0Iiwic3VwZXJoZXJvX2NvbG9yX2hlYWRpbmciOiIjNjY2NjY2In1d';
	$default_preset = theme_get_setting('superhero_default_preset');
	$default_preset = empty($default_preset)?0:$default_preset;
	//print theme_get_setting('default_preset');die;
	if($presets){
		$js = "var superhero_presets = ".base64_decode($presets)."; var superhero_current_preset = 0; var default_preset = {$default_preset}";
	}else{
		$js = "var superhero_presets = [{name:'Preset 1',superhero_color_link:'#00AFD1'},{name:'Preset 2',superhero_color_link:'#FF5A19'}]; var superhero_current_preset = 0; var default_preset = {$default_preset}";
	}
	drupal_add_js($js,'inline');
	drupal_add_js(drupal_get_path('theme','superhero').'/js/presets.js');
	
	$form['superhero_settings']['preset_settings'] = array(
		'#type' => 'fieldset',
		'#title' => t('Presets')
	);
	
	$color_attrs = array(
		'class' => array(
			'colorpicker',
			'perset-option'
		)
	);
	$form['superhero_settings']['preset_settings']['new_preset'] = array(
		//'#markup' => '<a href="#" class="new-preset">New preset</a><div class="presets"></div>',
		'#markup' => '<div class="presets"></div>',
	);
	
	$form['superhero_settings']['preset_settings']['superhero_color_main'] = array(
		'#type' => 'textfield',
		'#title' => t('Main Color'),
		'#default_value' => theme_get_setting('superhero_color_main'),
		'#attributes' => $color_attrs
	);
	
	$form['superhero_settings']['preset_settings']['superhero_color_text'] = array(
		'#type' => 'textfield',
		'#title' => t('Text Color'),
		'#default_value' => theme_get_setting('superhero_color_text'),
		'#attributes' => $color_attrs
	);
	
	$form['superhero_settings']['preset_settings']['superhero_color_link'] = array(
		'#type' => 'textfield',
		'#title' => t('Link Color'),
		'#default_value' => theme_get_setting('superhero_color_link'),
		'#attributes' => $color_attrs
	);
	
	$form['superhero_settings']['preset_settings']['superhero_color_hover'] = array(
		'#type' => 'textfield',
		'#title' => t('Hover Color'),
		'#default_value' => theme_get_setting('superhero_color_hover'),
		'#attributes' => $color_attrs
	);
	
	$form['superhero_settings']['preset_settings']['superhero_color_heading'] = array(
		'#type' => 'textfield',
		'#title' => t('Heading Color'),
		'#default_value' => theme_get_setting('superhero_color_heading'),
		'#attributes' => $color_attrs
	);
	$form['superhero_settings']['preset_settings']['superhero_presets'] = array('#type' => 'hidden', '#default_value' => theme_get_setting('superhero_presets'));
	$form['superhero_settings']['preset_settings']['superhero_default_preset'] = array('#type' => 'hidden', '#default_value' => theme_get_setting('superhero_default_preset'));
}