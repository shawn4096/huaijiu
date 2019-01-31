#include <ansi.h>

inherit ITEM;

void create()
{
   set_name("茯苓忘忧散", ({"wangyou san"}));
   if (clonep())
      set_default_object(__FILE__);
   else {
      set("value", 2000);
      set("unit", "份");
      set("long","这是一份茯苓忘忧散，用于消除各种异常状态。\n");

   }
   set_weight(100);
   setup();
}

int init()
{
   add_action("do_eat", "fu");
}

int do_eat(string arg)
{
   object me = this_player();

   if(!id(arg))
        return notify_fail("你要吃什么？\n");

        if( !me->query_condition("no_perform") 
           & !me->query_condition("no_exert") 
           & !me->query_condition("no_force") 
           & !me->query_condition("neishang") 
           & !me->query_condition("yyz_hurt") 
           & !me->query_condition("yzc_qiankun") 
           & !me->query_condition("fx_busy") 
           & !me->query_condition("hunyuan_hurt") 
           & !me->query_condition("no_enforce") )
              return notify_fail("以你目前的状态，不需要服用茯苓忘忧散。\n");

        me->clear_condition("no_perform");
        me->clear_condition("no_exert");
        me->clear_condition("no_force");
        me->clear_condition("neishang");
        me->clear_condition("yyz_hurt");
        me->clear_condition("yzc_qiankun");
        me->clear_condition("fx_busy");
        me->clear_condition("hunyuan_hurt");
        me->clear_condition("no_enforce");
        message_vision(HIR"$N服下一份茯苓忘忧散，一股清凉的气息自丹田涌上来。\n"NOR, this_player());
        destruct(this_object());
        return 1;
       
}
