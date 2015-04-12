#pragma once

#include <ssengine/render/types.h>
#include <complex>

struct transform
{
    std::complex<float> mul;
    std::complex<float> add;
};

struct ss_node2d
{
    ss_node2d();
    ~ss_node2d();

    void set_displace(float x, float y){
        displace = std::complex<float>(x, y);
        _require_recalc();
    }
    void set_rotation(float r){
        rotation = r;
        // crotation = std::complex<float>(cosf(r), sinf(r));
        _require_recalc();
    }
    void set_scale(float r){
        scale = r;
        _require_recalc();
    }

    void set_x(float x){
        set_displace(x, get_y());
    }
    void set_y(float y){
        set_displace(get_x(), y);
    }

    float get_x(){
        return displace.real();
    }
    float get_y(){
        return displace.imag();
    }
    float get_rotation(){
        return rotation;
    }
    float get_scale(){
        return scale;
    }

    void calc();
    const transform& get_transform(){
        calc();
        return transform;
    }

    void insert_first(ss_node2d* other);
    void insert_last(ss_node2d* other);

    void insert_after(ss_node2d* other);
    void insert_before(ss_node2d* other);

    void remove();

    ss_node2d* get_parent(){ return parent; }
    ss_node2d* get_prev(){ return prev; }
    ss_node2d* get_next(){ return next; }
    ss_node2d* get_first_child(){ return first_child; }
    ss_node2d* get_last_child(){ return last_child; }
private:
    void _require_recalc();
    void _require_update();
    std::complex<float> displace;
    float scale;
    float rotation;

    ss_node2d* prev;
    ss_node2d* next;
    ss_node2d* parent;
    ss_node2d* first_child;
    ss_node2d* last_child;

    transform   transform;
    bool        need_calc, need_update;
};
