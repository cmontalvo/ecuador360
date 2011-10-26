/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
(function ($) {
  Drupal.behaviors.cloud360 = {
    attach: function () {
      //Verify if exist the map
      if($('#gmap-map360-gmap0').offset()) {

        $('#map-filter').click(function(){
          alert('click');
        });

        //Load Zone Buttons
        b=document.createElement("DIV");
        var d=document.createElement("DIV");
        d.className="mapbtnglp";
        d.title="Galapagos";
        d.style.width="80px"

        b.appendChild(d);

        var n=document.createElement("DIV");
        n.className="mapbtnglp";
        n.title="Continente";
        n.style.width="80px"

        b.appendChild(n);

        var a=document.createElement("DIV");
        a.style.fontFamily="Arial,sans-serif";
        a.style.fontSize= "12px";
        a.style.paddingLeft="4px";
        a.style.paddingRight="4px";
        a.style.paddingTop="4px";
        a.style.width="50%";
        a.innerHTML="Galapagos";
        d.appendChild(a);

        //google.maps.event.addDomListener(d,"click",function(){map.setCenter(new google.maps.LatLng(-0.483393,-91.07666), 15);  });

        var m=document.createElement("DIV");
        m.style.fontFamily="Arial,sans-serif";
        m.style.fontSize= "12px";
        m.style.paddingLeft="4px";
        m.style.paddingRight="4px";
        m.style.paddingTop="4px";
        m.style.width="50%";
        //if (lang == "es")
        //m.innerHTML="Continente";
        //else
        //m.innerHTML="Mainland";
        n.appendChild(m);

        //google.maps.event.addDomListener(n,"click",function(){map.setCenter(new google.maps.LatLng(-1.30726,-78.706055), 7); });

        b.index=1;
      //map.controls[google.maps.ControlPosition.TOP_LEFT].push(b);
      }
    }
  };
}(jQuery));

function mapControls(controlDiv2, map, categories) {
  controlDiv = document.getElementById(controlDiv2);
  // Set CSS for the control border
  var controlUI = document.createElement('DIV');
  controlUI.style.backgroundColor = 'white';
  controlUI.style.borderStyle = 'solid';
  controlUI.style.borderWidth = '2px';
  controlUI.style.cursor = 'pointer';
  controlUI.style.textAlign = 'center';
  controlUI.title = 'Click to set the map to Home';
  controlDiv.appendChild(controlUI);

  // Set CSS for the control interior
  var controlText = document.createElement('DIV');
  controlText.className = 'map-footer';
  controlText.innerHTML = categories;
  controlUI.appendChild(controlText);
}

function map_close() {
  if(jQuery('.map-close-button .open').offset().top != 0) {
    jQuery('.map-close-button a').removeClass('open');
    jQuery('.map-footer').addClass('close');
    jQuery('.map-footer-wrapper').addClass('close');
  }
  else {
    jQuery('.map-close-button a').addClass('open');
    jQuery('.map-footer').removeClass('close');
    jQuery('.map-footer-wrapper').removeClass('close');
  }

}