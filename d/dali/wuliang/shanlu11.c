#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
���Ų����У��ٲ�̤���ľ��ǰ������ݣ�����û��·,ÿ��һ����������
���̵�С��,����������塣
LONG
        );
        set("outdoors", "dali");

        set("exits", ([
           "south" : __DIR__"shanlu11",
           "north" : __DIR__"shanlu11",
           "west" : __DIR__"shanlu11",
           "east" : __DIR__"shanlu11",
        ]));

        set("coor/x",-300);
  set("coor/y",-250);
   set("coor/z",-20);
   setup();
}


void init()
{    
        object me = this_player();
        if( me->query("dali/pass") && me->query_skill("lingbo-weibu", 1) < 140){
           me->move(__DIR__"gaoshan");
           message_vision("$N��Ϥ���ƹ�ɭ�֣�����һ����ɽ�ϡ�\n", me);
        }
        if (random(me->query("kar")) <10 && me->query_con() < 30){
           me->set_temp("last_damage_from", "��ɭ�����ƣ������");
           me->add("qi", -30);
           me->add("jingli", -10);
           me->receive_wound("jing", 20);
        }
        else{
             me->add("qi", -20);
        }    
        add_action("do_look", "look");               
}

int do_look()
{
        object me = this_player();
        mixed *local;
        local = localtime(time() * 60);
        if((local[2] < 3 || local[2] >= 21)&&!random(6)) {
        message("vision",BLU"�����,���������һƬ�����ֲ�����ָ,���Ĵ�������,��������־�.\n"
                           "ͻȻ��������Ұ�޵ĺ���,���ŵĿ�������.\n"NOR, me);
        }
}

int valid_leave(object me, string dir)
{
        mixed *local;
        local = localtime(time() * 60);
        if (dir == "west")
          me->add_temp("mark/steps",1);
        if (dir == "south")
          me->add_temp("mark/step",-1);
       if (dir == "east")
          me->add_temp("mark/steps",-1); 
        if (dir == "north")
          me->add_temp("mark/step",1);
/**for һ��,will be written later***
        if (me->query_temp("mark/steps") == -7 && me->query_temp("mark/step") == -4
            && random(me->query("kar"))>15
            && (local[2] < 3 || local[2] >= 21)){
            me->move(__DIR__"senlin-1");
            me->delete_temp("mark/steps");
            me->delete_temp("mark/step");
             return notify_fail("�������ţ�ͻȻ����ǰ���������һ��ƹ⡣\n");
         }  
*/
/**for Ӫ�ȶ��� ***/
         if (me->query_temp("mark/steps") == me->query_temp("duanyu/steps") 
           && me->query_temp("mark/step") == me->query_temp("duanyu/step")  
           && (random(me->query("kar"))+random(me->query("int"))) > 50
         && (random(me->query_con())+random(me->query_int())) > 75
           &&(local[2] < 6 || local[2] >= 3)
           && me->query_temp("duanyu/find2") ){
            me->move(__DIR__"gaoshan");
            log_file("quest/lbwb",sprintf("%s %s(%s)˳��ͨ��ɽ·������Ѱ���貨΢��֮·��\n",
                ctime(time())[4..19],me->name(1), capitalize(getuid(me))));
            me->set("dali/pass", 1);
            me->delete_temp("mark/steps");
            me->delete_temp("mark/step");
              return notify_fail("���ߵ���һ����ɽ�ϡ�\n");
         }

         if (me->query_temp("mark/steps") < -8 
          || me->query_temp("mark/step") < -8 
          || me->query_temp("mark/steps") > 10 
          || me->query_temp("mark/step") > 10 ){
           if(me->query_temp("duanyu/find2")){
               me->add("dali/fail", 1);
/*             log_file("quest/lbwb",sprintf("%s %s(%s)��%d�λ���û�����գ�δ��˳��ͨ��ɽ·��\n",
                ctime(time())[4..19],me->name(1), capitalize(getuid(me)),me->query("dali/fail") )); */

           }
           me->move(__DIR__"xiaoxi");
           me->delete_temp("mark/steps");
           me->delete_temp("mark/step");
           if(me->query_temp("duanyu/find2") && me->query("dali/fail") >= 999999999){
              me->delete_temp("duanyu");
              log_file("quest/lbwb",sprintf("%s %s(%s)���λ���û�����գ�ʧȥѰ���貨΢���Ļ��ᡣ\n",
                ctime(time())[4..19],me->name(1), capitalize(getuid(me))));
              return notify_fail(HIW"\n���ƣ�������߳����ɽ·����ɥ�ط����Լ���ôҲ�Ҳ����Ĵ���˵����١�\n"NOR);
           }
           else 
              return notify_fail("���ƣ�����������߳������ɽ·��\n");
        }           
        return ::valid_leave(me, dir);
}
