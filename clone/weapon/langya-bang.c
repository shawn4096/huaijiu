// langya.c

#include <weapon.h>
#include <ansi.h>
inherit STICK;

void create()
{
       set_name(RED"������"NOR, ({ "langya bang","bang" }));
       set_weight(15000);
       if (clonep())
               set_default_object(__FILE__);
       else {
               set("unit", "��");
               set("long", "����һ�����ִ������������\n");
               set("value", 2000);
               set("material", "steel");
               set("wield_msg", "$N��һ��$n�������С�\n");
               set("unwield_msg", "$N�����е�$n���¡�\n");
       }
 init_stick(50);
       setup();
}
