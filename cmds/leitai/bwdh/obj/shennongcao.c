#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG"��ũ��"NOR, ({"shennong cao"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("long", "����һ�ű��̵�С�ݣ��̺���������������ƺ������������Ƶ�ҩ��\n" NOR);
                set("no_sell", "��ô����ı����ô��������Ǯ��");
                set("medicine", "drug");
                set("make/drug", 1);
        }
        setup();
}
