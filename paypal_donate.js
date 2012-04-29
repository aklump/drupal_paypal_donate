// $Id: paypal_donate.js 187 2010-10-19 01:29:05Z aklump $

/**
 * @file
 * The main javascript file for the PayPal Donate module
 */

var paypalDonate = paypalDonate || {};


paypalDonate.checkValue = function(textbox) {
  //locate the submit button for this form
  var formId = textbox.parents('form:first').attr('id');
  var button = $('#' + formId + ' :submit');
      
  var amount = textbox.val();
  if (amount <= 0){
    button.addClass('disabled');
    return false;
  }
  else {
    button.removeClass('disabled');
    textbox.removeClass('error');
    return true;
  }
}

Drupal.behaviors.paypalDonate = function (context) {
  if (Drupal.jsEnabled){

    // scan and disable all buttons without user input values != 0
    // this degrades nicely w/o javascript
    $('.user-value:not(paypal-donate-processed)')
    .addClass('paypal-donate-processed')
    .each(function() {
      paypalDonate.checkValue($(this));
    });
    
    //when a user leaves the textbox, check and give the button life if value != 0
    $('.user-value').keyup(function() {
      paypalDonate.checkValue($(this));
    });
    
    $('.blank-amount .form-submit').click(function() {
    
      //locate the textbox for this form
      var formId = $(this).parents('form:first').attr('id');
      var textbox = $('#' + formId + ' .user-value');  
  
      if (!paypalDonate.checkValue(textbox)){
        textbox.addClass('error');    
        return false;
      }
      return true;
    });
  }
}