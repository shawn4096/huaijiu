// baihong-jian.c �׺罣

#include <weapon.h>

inherit SWORD;
inherit F_UNIQUE;
void create()
{
        set_name("�׺罣", ({ "baihong jian", "baihong", "sword" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","���ǰ��ֱ����������������������͸���׹⣬��������ޱȡ�\n");
                set("value", 3000);
                set("unique", 1);
                set("rigidity", 3);
                set("sharpness", 3);
                set("material", "blacksteel");
                set("weapon_prop/parry",2);
                set("wield_neili", 500);
                set("wield_maxneili", 900);
                set("wield_str", 22);
                set("treasure",1);
                set("wield_msg", "ֻ�������ˡ���һ�����׹���֣�$N��������µ�$n���ñ�ֱ��\n");
                set("unequip_msg", "$N�����е�$n�������䡣\n");
        }
        init_sword(50);
        setup();
}
