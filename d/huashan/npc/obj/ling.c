// ITEM: /d/huashan/npc/obj/ling.c
// Date: Look 99/03/25

inherit ITEM;

#include <ansi.h>
void create()
{
        set_name(YEL"����"NOR, ({ "ling pai","ling"}));
        set_weight(10);

        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
                        "����һö��ɽ�ɵ����Ʒ��������������ɽ�����������ʱ�������Լ����Ʒ���\n");
                set("value", 0);
                set("material", "iron");
         }
	setup();
}
