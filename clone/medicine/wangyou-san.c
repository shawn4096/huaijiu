#include <ansi.h>

inherit ITEM;

void create()
{
   set_name("��������ɢ", ({"wangyou san"}));
   if (clonep())
      set_default_object(__FILE__);
   else {
      set("value", 2000);
      set("unit", "��");
      set("long","����һ����������ɢ���������������쳣״̬��\n");

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
        return notify_fail("��Ҫ��ʲô��\n");

        if( !me->query_condition("no_perform") 
           & !me->query_condition("no_exert") 
           & !me->query_condition("no_force") 
           & !me->query_condition("neishang") 
           & !me->query_condition("yyz_hurt") 
           & !me->query_condition("yzc_qiankun") 
           & !me->query_condition("fx_busy") 
           & !me->query_condition("hunyuan_hurt") 
           & !me->query_condition("no_enforce") )
              return notify_fail("����Ŀǰ��״̬������Ҫ������������ɢ��\n");

        me->clear_condition("no_perform");
        me->clear_condition("no_exert");
        me->clear_condition("no_force");
        me->clear_condition("neishang");
        me->clear_condition("yyz_hurt");
        me->clear_condition("yzc_qiankun");
        me->clear_condition("fx_busy");
        me->clear_condition("hunyuan_hurt");
        me->clear_condition("no_enforce");
        message_vision(HIR"$N����һ����������ɢ��һ����������Ϣ�Ե���ӿ������\n"NOR, this_player());
        destruct(this_object());
        return 1;
       
}
