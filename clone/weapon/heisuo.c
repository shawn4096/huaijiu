#include <weapon.h>
#include <ansi.h>

inherit WHIP;
inherit F_UNIQUE;

void create()
{
        set_name("����",({ "hei suo", "whip","bian","suo" }) );
        set_weight(15000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("unique", 3);
                set("rigidity", 3);
                set("material", "steel");
                set("weapon_prop/dodge", 3);
                set("weapon_prop/parry", 1);
                set("treasure",1);
                set("wield_neili", 200);
                set("wield_maxneili", 800);
                set("wield_str", 20);
                set("long", "������ͨ������޹�ĳ���������һ��������צ��ī����ҹ���趯֮ʱ�Ʋ������Ӱ�ӡ�\n");                
                set("unwield_msg", "$N����һ������$n�̻����䡣\n");
                set("wield_msg", "$N����һ�������һ��$n�������С�\n");
        }
        init_whip(160);
        setup();
}
int wield()
{
    object ob=environment();
    int ret;
    if(!ob||!living(ob)) return 0;
    add("rigidity",ob->query_skill("whip")/50);
    if(query("rigidity")>9) set("rigidity",9);
    if( ret=::wield()) return ret;
    return 1;
}
