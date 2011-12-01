/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
function mapControls(controlDiv2, map, categories) {
  controlDiv = document.getElementById(controlDiv2);
  // Set CSS for the control border
  var controlUI = document.createElement('DIV');
  controlUI.style.backgroundColor = 'white';
  controlUI.style.borderStyle = 'solid';
  controlUI.style.borderWidth = '2px';
  controlUI.style.cursor = 'pointer';
  controlUI.style.textAlign = 'center';
  controlUI.title = '';
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