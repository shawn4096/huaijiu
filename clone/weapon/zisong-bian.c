// zisong-bian.c ���ɱ�
// Created by Numa@Sj 1999-11-23

#include <weapon.h>
#include <ansi.h>

inherit WHIP;
inherit F_UNIQUE;

void create()
{
        set_name(MAG"���ɱ�"NOR,({ "zisong bian", "whip","bian" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("unique", 1);
                set("rigidity", 3);
                set("material", "wood");
                set("weapon_prop/dodge", 5);
                set("treasure",1);
                set("wield_neili", 400);
                set("wield_maxneili", 1000);
                set("wield_str", 25);
                set("long", "����һ������ɽ�ز����������ɵı��ӣ���ӯС�ɣ����������������\n");
                set("unwield_msg", "$Nһ����������$n�̻����䡣\n");
                set("wield_msg", "$N������С������ĳ��һ��$n�������С�\n");
        }
        init_whip(80);
        setup();
}

