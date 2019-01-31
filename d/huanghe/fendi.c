inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",HIB"Ĺ��"NOR);
        set("long",@LONG
�ߵ�����Խ���е���������Ҷ������裬�Ĵ���������ľ���õ���ζ��û
ϥ���Ӳ�����һ�����أ�Ĺ��(bei) �������˳���������ϸ�������ѱ������
дЩʲô��Ĺǰ����ֽ�ң��������þ�û�����������ˡ�
LONG
        );
        
        set("no_fight", 1); 
        set("no_sleep_room", 1);
        set("dao_count",1);
        set("exits", ([
               "south"         : __DIR__"shulin6",
        ]) );

        set("objects",([
            __DIR__"npc/hu-fei" : 1,  
        ])); 

        set("item_desc", ([ 
                "bei"||"Ĺ��"||"��":@LONG
             ________
            /        \
           /          \
          |        ��  |
          |            |
          |        ��  |
          |     ��     |
          |     һ ��  |
          |     ��     |
          |     �� ��  |
          | ��  ��     |
          | ��         |
          | ��  ֮     |
          | ��         |
          |     Ĺ     |
          |            |
LONG
        ]) );
    
       set("coor/x",70);
  set("coor/y",80);
   set("coor/z",0);
   setup(); 
}
 
void init()
{
        add_action("do_wa", "wa");
}

int do_wa(string arg)
{
        object dao, me, ob;
        me = this_player();

        if( ! arg || arg != "di")
          return notify_fail("��Ҫ��ʲ�᣿\n");

        if( ob = present("hu fei",environment(me))) {
           message_vision("$N��һ��������������$n��\n", ob,me);
           return notify_fail(CYN"��쳺ȵ�����Ҫ�����ҵ�����徲��\n"NOR"�㲻�����ж�����\n");
        }
 
        if ((int)me->query("jingli") < 500) 
           return notify_fail("��ľ�������������£�\n");  
 
        if(random(10)!=6) {
           me->add("jingli",-200);
           return notify_fail("�㿴׼��Ĺ������֮�����˾���ָ������������\n");
           }

        dao = unew(BINGQI_D("blade/lengyue-dao"));

        if(!clonep(dao)){
             tell_room(environment(me), me->name() + "���˰��죬ֻŪ��һ���ࡣ\n", ({ me }));
             return notify_fail("�����˰��죬ֻŪ��һ���ࡣ\n");
        }

        if(clonep(dao) && dao->violate_unique()){
           destruct(dao);
           tell_room(environment(me), me->name() + "���˰��죬ֻŪ��һ���ࡣ\n", ({ me }));
           return notify_fail("�����˰��죬ֻŪ��һ���ࡣ\n");
        } 
        message_vision("�ڵ����ߣ�$N�е�˫����ָͬʱ����һ�������Ӳ֮�����������������һ�����ʵĵ�����\n"+
                       "$Nץס��������ѵ��������г�������г�������������⡣\n",me);
        me->add("jingli", -500);
        me->delete_temp("marks/ah1");
        me->delete_temp("marks/ah2");
        me->delete_temp("marks/ah3");
        dao->move(me);
        return 1;
}
