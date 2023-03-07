#pragma once

#include<QObject>
#include <QAbstractListModel>
#include <QAbstractItemModel>
#include <QTimer>
#include <QtQml/qqmlregistration.h>
#include"Hour_model.hpp"

class Day_box : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QDate day READ day CONSTANT)
    Q_PROPERTY(Hour_model* hour_model  READ hour_model CONSTANT)

public:

    Hour_model* hour_model(void)const{return hour_model_m;}
    QDate day(void){return day_m;}

    Day_box(QDate day_,Hour_model * hour_model_,QObject *parent):QObject(parent),day_m(day_),hour_model_m(hour_model_){
        hour_model_->setParent(this);
    };

private:
    Hour_model * const hour_model_m;
    QDate day_m;

};

class Day_model : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(int total_selected  READ total_selected  NOTIFY total_selected_changed)


public:

    explicit Day_model(QObject *parent = nullptr);
    enum ModelRoles {
        dayRole = Qt::UserRole + 1,
        hour_modelRole
    };

    std::vector<Booking> get_new_bookings(void);



    void add_to_total_selected(int sel){total_selected_+=sel; emit total_selected_changed(total_selected_);}

    int total_selected(void)const{return total_selected_;}


    void add_booking(const Booking nbook, bool sent);
    void remove_sent_booking(const Booking);

    void append(Day_box* o);
    void pop_front(void);
    void update_list(void);

    int count() const;
    int rowCount(const QModelIndex &p) const;
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;



signals:
    void countChanged(int count);
    void total_selected_changed(int sele);



private:
    int m_count;
    QList<Day_box*> m_days;
    QTimer *timer_m;
    int total_selected_;

};

