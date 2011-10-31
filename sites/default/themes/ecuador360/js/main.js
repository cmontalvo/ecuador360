(function ($) {
  Drupal.behaviors.ecuador360 = {
    attach: function () {
      //Set homepage links
      $('#block-menu-menu-homepage .english').attr('href', '/coverflow');
      $('#block-menu-menu-homepage .spanish').attr('href', '/es/coverflow');
      //Set the translation link
      $('.i18n-es #block-search-form .form-actions input.form-submit').val('Buscar');
      $('.i18n-es .footer-language').attr('href', window.location.pathname.replace(/\/es/g,""));
      $('.i18n-en .footer-language').attr('href', '/es' + window.location.pathname);
      //Set menu parameters
      $('.i18n-en .menu-hotels').attr('href', '/content/category-result?category=13');
      $('.i18n-es .menu-hotels').attr('href', '/es/content/category-result?category=13');
      $('.i18n-en .menu-restaurants').attr('href', '/content/category-result?category=6');
      $('.i18n-es .menu-restaurants').attr('href', '/es/content/category-result?category=6');
    }
  };
}(jQuery));

//Map Filter
(function ($) {
  $(document).ready(function() {
    $('#map-filter').click(function(){
      //Hide all markers
      $('#gmap-map360-gmap0 img').each(function() {
        if($(this).attr('id').indexOf('mtgt_unnamed_', 0) == 0) {
          $(this).addClass('hidden');
        }
      });
      $('.map-footer-wrapper .category input:checked').each(function() {
        //alert ($(this).closest('.category').children('.title').html());
        var type = $(this).closest('.category').children('.title').attr('rel');
        //Show filtered markers
        $('#gmap-map360-gmap0 img').each(function() {
          if($(this).attr('id').indexOf('mtgt_unnamed_', 0) == 0) {
            if($(this).attr('src').indexOf(type, 0) >= 0) {
              $(this).removeClass('hidden');
            }
          }
        });
      });
    });
  });
}(jQuery));

function mypopup(url) {
  mywindow = window.open
               (url +"","Ecuador360","width=800,height=400,top=200,left=230,resizable=1");
  //mywindow.moveTo(100,200);
 }

 /**
 * Function to render social share overlay
 */
function share_me(title, comment, url, rpxImageSrc) {
  RPXNOW.init({
    appId : 'jhbmdkiiogoimcklanon',
    xdReceiver : '/rpx_xdcomm.html'
  });
  
  RPXNOW.loadAndRun(['Social'], function() {
    var activity = new RPXNOW.Social.Activity(title, comment, url);
    var shareImage = new RPXNOW.Social.ImageMediaCollection();
    shareImage.addImage(rpxImageSrc, url);
    activity.setMediaItem(shareImage);
    RPXNOW.Social.publishActivity(activity);
  });
}