// yfzhen.c
// By River 98/09
#include <ansi.h>
inherit COMBINED_ITEM;
void create()
{
        set_name(HIY"�����" NOR, ({ "yufeng zhen", "zhen" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "�����������ϸ��ë���Ľ��룬���ɻƽ��ĳɾ��֣������β����\n"+
                            "��Һ��������ȻϸС������ƽ���أ�����ʱ�Կɼ�Զ��\n");
                set("unit", "��");
                set("no_sell", 1);
                set("value", 20);
                set("base_unit", "ö");
                set("base_weight", 200);
                set("material", "steel");
        }
        set_amount(10);
        setup();
}
