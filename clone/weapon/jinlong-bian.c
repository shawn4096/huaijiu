#include <weapon.h>
#include <ansi.h>

inherit WHIP;
inherit F_UNIQUE;

void create()
{
        set_name(HIY"������"NOR,({ "jinlong bian", "whip","bian","jinlong" }) );
        set_weight(15000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1500000);
                set("unique", 1);
                set("rigidity", 3);
                set("material", "steel");
                set("weapon_prop/dodge", 1);
                set("weapon_prop/parry", 1);
                set("treasure",1);
                set("wield_neili", 200);
                set("wield_maxneili", 800);
                set("wield_str", 22);
                set("long", "��������������ⱦ����ͨ�������˱�ʯ������ꡢ����֮����\n");
                set("unwield_msg", "$N����һ������$n�̻����䡣\n");
                set("wield_msg", "$N����һ�������һ��$n�������С�\n");
        }
        init_whip(70);
        setup();
}
