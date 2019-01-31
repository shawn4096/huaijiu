// jqdan.c ���鵤
// By River 99.5.25
#include <ansi.h>
inherit ITEM;

void create()
{
       set_name(HIG"���鵤"NOR, ({"jueqing dan", "dan","jueqing"}));
       set_weight(500);
       if (clonep())
             set_default_object(__FILE__);
       else {
             set("unit", "ö");
             set("long","����һö���ķ������Ӱ�ĵ�ҩ��ɫ����ڣ��ȳ��̱ǡ�\n");
             set("value", 1000);
             set("unique", 1);
             set("no_give", 1);
             set("no_drop", 1);
             set("no_get", 1);
             }
             setup();
}

int init()
{
       add_action("do_eat", "eat");
       add_action("do_mix", "mix");
}

int do_eat(string arg)
{
       object me = this_player();
       if(!id(arg))
             return notify_fail("��Ҫ��ʲô��\n");
       message_vision("$N����һö" + name() + "��\n", me);
       if ((int)me->query_condition("qinghua_poison") > 0) {
          me->clear_condition("qinghua_poison");
          tell_object(me,"��ֻ������ָʹ��������黨֮����Ȼ��ȥ��\n");
          }
       destruct(this_object());
       return 1;
}

int do_mix(string arg)
{
       object me = this_player();
       object thing,ob;

       if(!id(arg))
             return notify_fail("��Ҫ���ʲô��\n");

       thing = present("duanchang cao", me);
       if (!thing || !thing->query("credit") ) 
	      return notify_fail("��û�жϳ��ݣ���λ��!\n");

       message_vision("$N�����鵤��ϳ��ݻ����һ��\n", me);
       destruct(thing);

       if (random(50) > 47) {
          ob=unew("/d/gumu/jqg/obj/jqdan1");
          ob->move(me);
          tell_object(me,"��ҩ�����ɹ�����������ȥ��!\n");
          destruct(this_object());
          return 1;
          }
       tell_object(me,"�㼸��Ŭ�������ַ��������죬��ҩ����ʧ�ܡ�\n");
       destruct(this_object());
       return 1;
}
