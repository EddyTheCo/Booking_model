import QtQuick.Controls
import MyDesigns
import booking_model
import QtQuick

ApplicationWindow {
    visible: true
    id:window

    Day_model
    {
        id:daymodel
    }
    MyPayPopUp
    {
        id:paypopup
        addr_:""
        descr_:""
        visible:false
        closePolicy: Popup.CloseOnPressOutside
        anchors.centerIn: Overlay.overlay
    }

    Rectangle
    {
        anchors.fill:parent
        color:"#0f171e"
    }

    Day_swipe_view
    {
        anchors.fill: parent
        day_model:daymodel
        can_book:true
        popup:paypopup
    }


}
