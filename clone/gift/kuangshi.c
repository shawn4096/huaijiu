
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("������ʯ", ({ "yun shi" , "shi" }));
        set_weight(3000+random(5000));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",HIC"��֪���������ʼ�Ӳ���ƺ�������������������\n"NOR);
                set("value", 3000);
                set("weapon_pro",1);
                set("no_cun", 1);
                set("no_sell","ϡ��Źֵ�һ��ʯͷ��Ҫ�����ã�");
        }
        setup();
}
