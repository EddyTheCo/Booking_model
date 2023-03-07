import QtQuick 2.0
import QtQuick.Controls
import booking_model
import MyDesigns

SwipeView {
    id: swipe_view
    required property Day_model day_model
    required property bool can_book
    required property MyPayPopUp popup
    currentIndex: 0

    Repeater {
        model: swipe_view.day_model
        delegate: Dia_delegate {
            can_book:swipe_view.can_book
            popup:swipe_view.popup
        }
    }


}



