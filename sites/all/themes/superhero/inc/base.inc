<?php

class superhero_theme {
	var $theme;
	var $settings;
	var $sections;
	var $regions;
	var $scss;
	var $page;
	var $custom = array();
	function __construct($theme) {
		$this->theme = $theme;
		$this->init();
	}
	
	function init() {
		$this->settings();
		$this->sections();
		$this->regions();
		$this->scss();
	}
	
	function settings() {
		if (!isset($this->settings)) {
			$presets = json_decode(base64_decode(theme_get_setting('superhero_presets',$this->theme)));
			$default_preset = isset($_SESSION['superhero_default_preset'])?$_SESSION['superhero_default_preset']:theme_get_setting('superhero_default_preset',$this->theme);
			$custom_preset = isset($_GET['preset'])?str_replace('preset','',$_GET['preset']):'';
			if(is_numeric($custom_preset)){
				$custom_preset--;
				if(isset($presets[$custom_preset])){
					$default_preset= $custom_preset;
				}
			}
			$_SESSION['superhero_default_preset'] = $default_preset;
		
			$preset = isset($presets[$default_preset])?$presets[$default_preset]:null;
			//Non superhero theme
			if(empty($preset)){
				$preset = new stdClass();
				$preset->superhero_color_main = '';
				$preset->superhero_color_text = '';
				$preset->superhero_color_link = '';
				$preset->superhero_color_hover = '';
				$preset->superhero_color_heading = '';
			}
			$this->settings = array(
				'responsive' => superhero_theme_get_setting('superhero_responsive',1,$this->theme),
				'color_main' => isset($preset->superhero_color_main)?$preset->superhero_color_main:'',
				'color_text' => $preset->superhero_color_text,
				'color_link' => $preset->superhero_color_link,
				'color_hover' => $preset->superhero_color_hover,
				'color_heading' => $preset->superhero_color_heading,
				'default_preset' => $default_preset
			);
			
		}
		return $this->settings;
	}
	
	function sections() {
		if (!isset($this->sections)) {
			$this->sections = array();
			
			if ($sections = superhero_info('sections',$this->theme)) {
				foreach($sections as $section => $title) {
					$this->sections[$section] = array(
						'section' => $section,
						'name' => $title,
						'enabled' => superhero_section_get_setting('enabled',$section,1,$this->theme),
						'weight' => superhero_section_get_setting('weight',$section,0,$this->theme),
						'primary' => superhero_section_get_setting('primary',$section,0,$this->theme),
						'fullwidth' => superhero_section_get_setting('fullwidth',$section,0,$this->theme),
						'backtype' => superhero_section_get_setting('backtype',$section,0,$this->theme),
						'backcolour' => superhero_section_get_setting('backcolour',$section,'',$this->theme),
						'backimage' => superhero_section_get_setting('backimage',$section,'',$this->theme),
						'vphone' => superhero_section_get_setting('vphone',$section,0,$this->theme),
						'vtablet' => superhero_section_get_setting('vtablet',$section,0,$this->theme),
						'vdesktop' => superhero_section_get_setting('vdesktop',$section,0,$this->theme),
						'hphone' => superhero_section_get_setting('hphone',$section,0,$this->theme),
						'htablet' => superhero_section_get_setting('htablet',$section,0,$this->theme),
						'hdesktop' => superhero_section_get_setting('hdesktop',$section,0,$this->theme),
						'sticky' => superhero_section_get_setting('sticky',$section,0,$this->theme),
						'style_margin' => superhero_section_get_setting('style_margin',$section,0,$this->theme),
						'style_padding' => superhero_section_get_setting('style_padding',$section,0,$this->theme),
						'style_background' => superhero_section_get_setting('style_background',$section,0,$this->theme)
					);
				}
			}
			uasort($this->sections,'drupal_sort_weight');
		}
		return $this->sections;
	}
	
	function regions() {
		if (!isset($this->regions)) {
			$this->sections();
			$this->regions = array();
			$exclude = array('page_top','page_bottom');
			
			foreach(system_region_list($this->theme) as $region => $title) {
				if (!in_array($region,$exclude)) {
					$section = superhero_region_get_setting('section',$region,NULL,$this->theme);
					//$columns = superhero_region_get_setting('columns',$region,NULL,$this->theme);
					$xscolumns = superhero_region_get_setting('xscolumns',$region,NULL,$this->theme);
					$smcolumns = superhero_region_get_setting('smcolumns',$region,NULL,$this->theme);
					$mdcolumns = superhero_region_get_setting('mdcolumns',$region,NULL,$this->theme);
					$lgcolumns = superhero_region_get_setting('lgcolumns',$region,NULL,$this->theme);
					
					$section = isset($section) && isset($this->sections[$section]) ? $section : NULL;
					
					$this->regions[$region] = array(
						'region' => $region,
						'name' => $title,
						'section' => $section,
						'enabled' => isset($section),
						//'columns' => $columns,
						'xscolumns' => $xscolumns,
						'smcolumns' => $smcolumns,
						'mdcolumns' => $mdcolumns,
						'lgcolumns' => $lgcolumns,
						//'width' => $columns,
						'weight' => superhero_region_get_setting('weight',$region,0,$this->theme),
						'force' => superhero_region_get_setting('force',$region,0,$this->theme)
					);
				}
			}
			uasort($this->regions,'drupal_sort_weight');
		}
		return $this->regions;
	}
	
	function scss() {
		if (!isset($this->scss)) {
			$scss_files = superhero_info('scss',$this->theme);
			$this->scss = $scss_files;
		}
		return $this->scss;
	}
}