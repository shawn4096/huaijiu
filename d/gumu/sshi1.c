#include <ansi.h>
inherit ROOM;

void create()
{ 
       set("short",HIC"ʯ��"NOR);
       set("long", @LONG
����Ҳ������֮������̧ͷ�����������Ҷ����������д�����ּ����ţ�
�㿴��һ�ᣬ���������ѽ⡣�Ҷ����Ͻǻ���һ��ͼ�������书�޹أ�����ϸ
���������Ƿ���ͼ��ʯ�����·������������(down)�ߡ�
LONG
     );
        set("item_desc", ([
             "down": HIB"�ں����ģ��������С�\n"NOR,
        ]));
        set("exits", ([
              "up" : __DIR__"shiguan",                 
        ]));
        setup();
}

void init()
{
        add_action("do_look", "look"); 
        add_action("do_look", "kan");
        add_action("do_walk", "walk");
        add_action("do_study", "yandu");
}

int do_look(string arg)
{
        object me=this_player();
        if ( arg =="map") {
            write(HIY"���������Ƿ�ͼ�����в��ɴ�ϲ��ԭ���ǻ�����ǳ�Ĺ���ص���\n"NOR);
            me->set_temp("map", 1);
            me->start_busy(1);
            return 1;         
        }
        if ( arg =="ceiling") {
            write(HIY"�㿴���Ҷ��������Ķ������������С�֡�\n"NOR);
            me->set_temp("ceiling", 1);
            me->start_busy(1);
            return 1;         
        }
        if ( arg =="zi") {
            write(HIY"��������ЩС�֣��ƺ�����һЩ�书Ҫ����\n"NOR);
            if( !me->query_temp("ceiling")
             || me->query("combat_exp", 1) < 1000000 ){
               tell_object(me,HIY"��������д�ļ����Ѷ����㿴��һ��ͷ����ˡ�\n"NOR);
               return 1;
            }
            if(( random(me->query_kar()) > 27
             && me->query("jiuyin/gumufail") < 30000 
               && random(me->query_int()) > 25)
             || me->query("jiuyin/gumu")){
//            write(HIW"�㶸ȻһƳ�䣬��������С�֡������澭�ڹ�Ҫ���������˷ܼ��ˡ�\n"NOR);
              write(HIW"���о���һ�£�����Ӧ�����ж�(yandu)Щ���ħȭ��(dafumo-quan)��\n"NOR);
              write(HIW"�����湦(jiuyin-zhengong)�Լ�������(jiuyin-shenfa)��Ƥë��\n"NOR);
              if( !me->query("jiuyin/gumu"))
              log_file("quest/jiuyin",sprintf("%s %s(%s)ʧ��%s�κ��ڹ�Ĺʯ���ϵõ������澭��\n",
                  ctime(time())[4..19], me->name(1),capitalize(getuid(me)),chinese_number(me->query("jiuyin/gumufail")) ));
              me->set("jiuyin/gumu", 1);
            }
            else {
              if( me->query("jiuyin/gumufail") <= 3 )
              me->add("jiuyin/gumufail", 1);
              if ( me->query("jiuyin/gumufail") < 3 )
              log_file("quest/jiuyin",sprintf("%s %s(%s)���%s�Σ�û�з��ֹ�Ĺʯ���ϵľ����澭��\n",
                      ctime(time())[4..19], me->name(1),capitalize(getuid(me)),chinese_number(me->query("jiuyin/gumufail")) )); 
              if( me->query("jiuyin/gumufail") == 300000)
              log_file("quest/jiuyin",sprintf("%s %s(%s)������Σ��޷��ٷ��ֹ�Ĺʯ���ϵľ����澭��\n",
                      ctime(time())[4..19], me->name(1),capitalize(getuid(me)))); 
              write(HIY"��������д�ļ����Ѷ����㿴��һ��ͷ����ˡ�\n"NOR);
            }
            me->delete_temp("ceiling");
            return 1;         
        }
        return notify_fail("��Ҫ��ʲô��\n");
}

int do_walk(string arg)
{ 
        object me=this_player();
        if (me->is_busy() || me->is_fighting())
              return notify_fail("����æ���ģ�\n");
        if ( arg =="down"){ 
//             if(!me->query_temp("map"))
//                   return notify_fail("������������ߣ�������ԥ������������˽š�\n");      
           tell_object(me,HIM"\n�㶫ת���䣬Խ��Խ�͡�ͬʱ���½�����ʪ��������Լ��ȥ���������ǲ����\n"+
                             "����һ�ᣬ��·�涸�����Ǳ�ֱ���¡��½���ԼĪ���ʱ������·��ƽ��ֻ��\n"+
                             "ʪ��ȴҲ���أ�������������������ˮ����·��ˮû���ס�Խ��ˮԽ�ߣ�����\n"+
                             "�������������롣\n"NOR);
           me->delete_temp("map");
           me->move(__DIR__"gmanhe1");
           tell_room(environment(me), me->name() + "��"HIC"ʯ��"NOR"�첽���˹�����\n", ({ me }));
           return 1;
        }
        return notify_fail("����ʯ����������ȥ����֪����Ǻã�\n");
}

int do_study(string arg)
{
      int cost, my_skill;
      object me=this_player();

      if (!arg) return 0;

      if( ! me->query("jiuyin/gumu"))
          return notify_fail("ʲô��\n");

      if(me->is_busy())
          return notify_fail("��������æ���ء�\n");

      if( me->is_fighting() )
          return notify_fail("���޷���ս����ר�������ж���֪��\n");

      if( !me->query_skill("literate", 1) )
          return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");

      if((int)me->query("potential") < 1 )
          return notify_fail("���Ǳ���Ѿ������ˣ�����ô��Ҳû�á�\n");

      if((int)me->query("combat_exp") < 1000000 )
          return notify_fail("���ʵս���鲻�㣬����ô��Ҳû�á�\n");

      if( me->query_int() < 40 )
          return notify_fail("����Ŀǰ��������������û�а취ѧ������ܡ�\n");

      cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
      if (cost < 20) cost = 20;
      if( me->query("neili") < cost * 2 + 300)
          return notify_fail("��������������޷����������ܡ�\n");
      me->set_temp("last_damage_from", "�ж������书�������Ļ���");

      switch (arg) {
        case "jiuyin-zhengong":
          my_skill = me->query_skill("jiuyin-zhengong", 1);
          if( my_skill >= 150)
              return notify_fail("������ⶴ���������Ѿ�̫ǳ�ˣ�����ѧ��ʲô������\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("Ҳ����ȱ��ʵս���飬��Զ��������������޷���ᡣ\n");
          else
              write("���ж����йؾ����湦�ļ��ɣ��ƺ���Щ�ĵá�\n");
          me->improve_skill("jiuyin-zhengong", ((int)me->query_skill("literate", 1)/5 + 1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          me->add("potential", - random(2));
          break;             
        case "jiuyin-shenfa":
          my_skill = me->query_skill("jiuyin-shenfa", 1);
          if( my_skill >= 150)
              return notify_fail("������ⶴ���������Ѿ�̫ǳ�ˣ�����ѧ��ʲô������\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("Ҳ����ȱ��ʵս���飬��Զ��������������޷���ᡣ\n");
          else
              write("���ж����йؾ������ļ��ɣ��ƺ���Щ�ĵá�\n");
          me->improve_skill("jiuyin-shenfa", ((int)me->query_skill("literate", 1)/5+1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          me->add("potential", - random(2));
          break;
        case "dafumo-quan":
          my_skill = me->query_skill("dafumo-quan", 1);
          if( my_skill >= 150)
              return notify_fail("������ⶴ���������Ѿ�̫ǳ�ˣ�����ѧ��ʲô������\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("Ҳ����ȱ��ʵս���飬��Զ��������������޷���ᡣ\n");
          else
              write("���ж����йش��ħȭ���ļ��ɣ��ƺ���Щ�ĵá�\n");
          me->improve_skill("dafumo-quan", ((int)me->query_skill("literate", 1)/5+1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          me->add("potential", - random(2));
          break;
      }
      return 1;
}
