(function ($) {
  Drupal.behaviors.ecuador360 = {
    attach: function () {
      //Set homepage links
      $('#block-menu-menu-homepage .english').attr('href', '/coverflow');
      $('#block-menu-menu-homepage .spanish').attr('href', '/es/coverflow');
      //Set the translation link
      $('.i18n-es #block-search-form .form-actions input.form-submit').val('Buscar');
      $('.i18n-es .footer-language').attr('href', window.location.pathname.replace(/\/es/g,"") + window.location.search);
      $('.i18n-en .footer-language').attr('href', '/es' + window.location.pathname + window.location.search);
      //Set menu parameters
      $('.i18n-en .menu-hotels').attr('href', '/content/category-result?category=103');
      $('.i18n-es .menu-hotels').attr('href', '/es/content/category-result?category=103');
      $('.i18n-en .menu-restaurants').attr('href', '/content/category-result?category=104');
      $('.i18n-es .menu-restaurants').attr('href', '/es/content/category-result?category=104');
      $('.i18n-en .menu-ranking').attr('href', '/content/category-result?category=all');
      $('.i18n-es .menu-ranking').attr('href', '/es/content/category-result?category=all');
      //Change login title
      $('.i18n-es .rpx-links a').each(function() {
        if($(this).html() == 'Sign in using one of these accounts:') {
          $(this).html('Accede a través de una de estas cuentas:');
        }
      });
      //Fix active class on hotels, restaurants and ranking
      switch (window.location.search) {
        case '?category=103':
          $('.menu-restaurants').removeClass('active');
          break;
        case '?category=104':
          $('.menu-hotels').removeClass('active');
          break;
        case '?category=all':
          $('.menu-restaurants').removeClass('active');
          $('.menu-hotels').removeClass('active');
          $('.menu-ranking').addClass('active');
          break;
      }
      //Fix News Active
      switch (window.location.pathname) {
        case '/aggregator/category/2':
          $('.menu-news').addClass('active');
          break;
        case '/es/aggregator/categories/2':
          $('.menu-news').addClass('active');
          break;
      }
      //Fix Search Click
      $('#block-search-form .form-type-textfield').click(function(){
        if($('#block-search-form .form-type-textfield input').val().length >= 2) {
          $('#block-search-form .form-actions input').click();
        }
      });
    }
  };
}(jQuery));

//Map Filter
(function ($) {
  $(document).ready(function() {
    //All selected
    $('.map-footer input').click(function() {
      if($(this).attr('id') == '-1') {
        $('.map-footer-wrapper .category input:checked').each(function() { 
          if($(this).attr('id') != '-1') {
            $(this).attr('checked', false);
          }
        });
      } else {
        if($(this).attr('checked') == true) {
          $('.map-footer input#-1').attr('checked', false);
        }
      }
    });
    //Filter Click
    $('#map-filter').click(function() {
      showAll = true;
      $('.map-footer-wrapper .category input:checked').each(function() {
        showAll = false;
      });
      if(showAll) {
        if($('.i18n-es').offset().top > 0) {
          alert('Debe seleccionar un filtro por lo menos.');
        } else {
          alert('You must select at least one filter.');
        }
      } else {
        //Hide all markers
        $('#gmap-map360-gmap0 img').each(function() {
          if($(this).attr('id').indexOf('mtgt_unnamed_', 0) == 0) {
            $(this).addClass('hidden');
          }
        });
        $('.map-footer-wrapper .category input:checked').each(function() {
          var type = $(this).closest('.category').children('.title').attr('rel');
          showAll = false;
          if($(this).attr('id') == -1) {
            showAll = true;
          }
          //Show filtered markers
          $('#gmap-map360-gmap0 img').each(function() {
            if($(this).attr('id').indexOf('mtgt_unnamed_', 0) == 0) {
              if(showAll) {
                $(this).removeClass('hidden');
              }
              else {
                if($(this).attr('src').indexOf(type, 0) >= 0) {
                  $(this).removeClass('hidden');
                }
              }
            }
          });
        });
      }
    });
  });
}(jQuery));

function mypopup(url) {
  mywindow = window.open
               (url +"","Ecuador360","width=800,height=400,top=200,left=230,resizable=1");
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