// changbian.c ����
#include <ansi.h>
#include <weapon.h>
inherit WHIP;

void create()
{
        set_name(BLK"�Žڱ�"NOR, ({ "Jiujie bian", "bian" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ����Ѱ����ϸ�ޣ��ɾŽ�ˮţƤ������֯���ɡ�\n");
                set("value", 100);
                set("material", "leather");
                set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_whip(50);
        setup();
}

