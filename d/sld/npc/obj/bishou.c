// bishou.c ذ��

#include <weapon.h>
inherit HOOK;

void create()
{
	string * pre=({"��","��","ͭ","��","��"});

        set_name(pre[random(sizeof(pre))]+"ذ��", ({ "bishou"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����Ƶ�ذ�ס�\n");
                set("value", 30);
                set("material", "steel");
        }
        init_hook(40);
        setup();
}
