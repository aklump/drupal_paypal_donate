<?php
// $Id: paypal_donate.admin.inc 193 2010-11-24 22:53:19Z aklump $ 

/** 
 * @file 
 * Administration page callbacks for the paypal_donate module. 
 */ 

/** 
 * Form builder. Configure paypal_donate. 
 * 
 * @ingroup forms 
 * @see system_settings_form(). 
 */ 
function paypal_donate_admin_settings() {
  global $base_url;
  
  //has the user defined how many blocks they want?
  $total_blocks = variable_get('paypal_donate_total_blocks', 1);
  
  $form['paypal_donate_total_blocks'] = array(
    '#type' => 'select',
    '#title' => t('Total donation blocks to create?'),
    '#description' => t('This is usually one, unless you want to assign blocks to multiple regions or have different donation configurations in different places in your website. Note: You can only increase this number unless you reinstall this module.'),
    '#default_value' => $total_blocks,
    '#options' => array_combine(range($total_blocks, 15), range($total_blocks, 15)),
  );
  
  for ($delta = 1; $delta <= $total_blocks; ++$delta) {
    
    //populate defaults with last block
    $prev_delta = max($delta - 1, 1);
    
    //fieldset wrapper
    $form['paypal_donate_block_'. $delta] = array(
      '#type' => 'fieldset',
      '#title' => t('Block #@num Configuration', array(
        '@num' => $delta,
      )),
      '#collapsible' => TRUE,
      '#collapsed' => $delta != 1,
    );
    
    $form['paypal_donate_block_'. $delta]['paypal_donate_paypal_account_'. $delta] = array(
      '#type' => 'textfield',
      '#title' => 'Your PayPal Account Login (primary email address)',
      
      //default to the first one if available
      '#default_value' => variable_get('paypal_donate_paypal_account_'. $delta, variable_get('paypal_donate_paypal_account_'. $prev_delta, NULL)),
      '#description' => t('Money will be deposited into this account. <strong>Do Not</strong> enter your paypal password!!!'),
      '#required' => TRUE, 
    );    

    $form['paypal_donate_block_'. $delta]['paypal_donate_product_'. $delta] = array(
      '#type' => 'textfield',
      '#title' => t('Product description'),
      '#default_value' => variable_get('paypal_donate_product_'. $delta, variable_get('paypal_donate_product_'. $prev_delta, t('Online Donation to @site', array('@site' => variable_get('site_name', $base_root))))),  
      '#description' => t('Enter a product name or description to show up on the paypal receipt.'),
      '#required' => TRUE, 
    );
    
    $form['paypal_donate_block_'. $delta]['paypal_donate_buttons_'. $delta] = array(
      '#type' => 'textarea',
      '#title' => t('Button Dollar Amounts'),
      '#default_value' => variable_get('paypal_donate_buttons_'. $delta, variable_get('paypal_donate_buttons_'. $prev_delta,'10,50,100,?')),
      '#rows' => 3,
      '#description' => t('Enter an amount for each button you wish to have on your form; separate amounts by a comma.  If you want the user to type in their own amount, enter a question mark (?) instead of a number. They will appear in the order you enter them.  <strong>E.g. 5,10,25,50,?</strong>'),
      '#required' => TRUE, 
    );
    
    $form['paypal_donate_block_'. $delta]['paypal_donate_return_url_'. $delta] = array(
      '#type' => 'textfield',
      '#title' => 'Thank You Page Url',
      '#field_prefix' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
      '#size' => 40,
      '#default_value' => variable_get('paypal_donate_return_url_'. $delta, variable_get('paypal_donate_return_url_'. $prev_delta, 'thank-you-for-your-donation')),
      '#description' => t('After a user makes a donation, where should they be taken on your website.  Enter the complete webpage address beginning with http://. <strong>Please make sure you create this page before accepting donations.</strong>'),
      '#required' => TRUE, 
    );

    $form['paypal_donate_block_'. $delta]['advanced'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['paypal_donate_block_'. $delta]['advanced']['paypal_donate_message_'. $delta] = array(
      '#type' => 'textarea',
      '#title' => t('Donation Message'),
      '#default_value' => variable_get('paypal_donate_message_'. $delta, variable_get('paypal_donate_message_'. $prev_delta, t('You may donate by clicking a button below.'))),
      '#rows' => 3,
      '#description' => t('Enter a short message to appear above the donation buttons.'),
      '#required' => FALSE, 
    );
    
    $form['paypal_donate_block_'. $delta]['advanced']['paypal_donate_button_face_'. $delta] = array(
      '#type' => 'textfield',
      '#title' => t('Button Label (for user input amounts only)'),
      '#default_value' => variable_get('paypal_donate_button_face_'. $delta, variable_get('paypal_donate_button_face_'. $prev_delta, t('Go'))),
    );
    
    $form['paypal_donate_block_'. $delta]['advanced']['paypal_donate_amount_location_'. $delta] = array(
      '#type' => 'select',
      '#title' => t('Display the Dollar Amount'),
      '#default_value' => variable_get('paypal_donate_amount_location_'. $delta, variable_get('paypal_donate_amount_location_'. $prev_delta, 'face')),
      '#options' => array(
        'face' => t('Inside the button'),
        'left' => t('To the left of the button (use css to style buttons)'),
      ),
      '#description' => t('Where do you wan the dollar amount to print in relationship to the button.  Experiment to see the difference.  This option allows for greater css override ability.'),
    );
    
    $form['paypal_donate_block_'. $delta]['advanced']['paypal_donate_new_window_'. $delta] = array(
      '#type' => 'select',
      '#title' => t('Open PayPal in a new browser window?'),
      '#default_value' => variable_get('paypal_donate_new_window_'. $delta, variable_get('paypal_donate_new_window_'. $prev_delta, 1)),
      '#options' => array(
        1 => t('Yes'),
        0 => t('No'),
      ),
    );

    $paypal_logo = 'https://www.paypal.com/en_US/i/logo/PayPal_mark_50x34.gif';
    
    $form['paypal_donate_block_'. $delta]['advanced']['chosen_logo_'. $delta] = array(
      '#value' => '<img style="display: block; margin-bottom: 10px;" src="'. check_plain(variable_get('paypal_donate_logo_'. $delta, $paypal_logo)) .'" />',
    );
    
    $form['paypal_donate_block_'. $delta]['advanced']['paypal_donate_logo_'. $delta] = array(
      '#type' => 'textfield',
      '#title' => t('Small Logo or Icon'),
      '#default_value' => variable_get('paypal_donate_logo_'. $delta, variable_get('paypal_donate_logo_'. $prev_delta, $paypal_logo)),
      '#description' => t('Enter the url to a small logo to be displayed at the bottom of your donation block, such as the PayPal logo (<a href="@url" target="_blank">Get PayPal logos.</a>).  You may leave this blank for no logo to appear.', array(
        '%pplogo' => $paypal_logo,
        '@url' => 'https://www.paypal.com/cgi-bin/webscr?cmd=xpt/general/OnlineLogoCenter-outside',
      )),
      '#required' => FALSE, 
    );    
  }
 
  return system_settings_form($form); 
}

/**
 * Form validation handler for paypal_donate_admin_settings_form().
 *
 * @see paypal_donate_admin_settings_form()
 * @see paypal_donate_admin_settings_form_submit()
 */
function paypal_donate_admin_settings_form_validate($form, &$form_state) {
  for ($delta = 1; $delta < $values['paypal_donate_total_blocks']; ++$delta) {
    if (!valid_email_address($form_state['values']['paypal_donate_paypal_account_'. $delta])) {
      form_set_error('paypal_donate_paypal_account_'. $delta, t('Your PayPal account should be a valid email address; what you provided is not.'));
    }
  }
}