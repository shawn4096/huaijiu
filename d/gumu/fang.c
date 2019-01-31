// fang.c 
// By River 98/10
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIC"ʯ��"NOR);
        set("long",@long
һ��յ�����ʯ�ң���ǰ������һ����̳������ʷ���һЩ�Ϲ���������
��ɢ����ҡҷ�Ļ�⣬һЩ��Ĺ���������ַ���Ĺ��������׼��ʷ��ڼ�̳��
��������ο�����Ӣ�顣
long);

        set("exits",([
        "north" : __DIR__"gmqs",
        "south" : __DIR__"gmcc",
        "east" : __DIR__"yaofang",
        ]));

        setup();
}

void init()
{
     add_action("do_jibai","jibai");
     add_action("do_ketou","ketou"); 
}

int do_jibai(string arg)
{
        object me,ob;
        int exp,pot;
        me=this_player();       
        ob = present("head", me);
        if ( arg == "head") {
          if(!ob )
              return notify_fail("��û����ͷ������ʲô��\n");        
          if(!me->query_temp("gm/job")) 
              return notify_fail("�㻹ûȥѲ���أ�����������׼���\n");
          if(ob->query("name") != "����Ů�ӵ��׼�")
              return notify_fail("������Ū������ͷ�����˺����ǹ�Ĺ���氡��\n");        
          if(ob->query("victim_user")) 
              return notify_fail("������Ū�����׼���ɱ�����˰ɣ�\n");
          if(ob->query("kill_by") != me)
              return notify_fail("���������ɱ�İɣ�������ô�õ������ͷ�ģ�\n");
          message_vision(HIY"$N���������ؿ��˼�����ͷ��Ȼ��������$n�ʷ��ڼ�̳���ࡣ\n"NOR,me,ob);
          if (random(20)> 18){ exp= 40+random(10); pot = exp*3 - random(20);}
          else { exp =160+random(50); pot= exp/6 + random(exp/10);}
	  me->add("combat_exp", exp);
          me->add("potential",pot);
          if(((int)me->query("potential", 1) + pot) > (int)me->query("max_pot", 1))
            me->set("potential", (int)me->query("max_pot", 1));
          me->delete_temp("gm/job");
          me->delete_temp("meet_nuzi");        
          call_out("destroying", 1, ob);
          tell_object(me,HIW"�㱻�����ˣ�"+ chinese_number(exp)+"��ʵս�����"+ chinese_number(pot) + "��Ǳ�ܡ�\n"NOR);
          return 1;
        }
        return notify_fail("����ʲô���ݰ���\n");
}

void destroying(object ob)
{
        destruct(ob);
        return;
}

int do_ketou(string arg)
{
        mapping fam;
        object me=this_player();
        if (!(fam = me->query("family")) || fam["family_name"] != "��Ĺ��")
           return notify_fail("�㲻�ǹ�Ĺ���ˣ��ڴ˿�ͷ������\n");
        if ( arg == "jitan"){
          if ( me->query("combat_exp") < 30000)
              return notify_fail("�㿴�ż�̳���ĸ�����̫����ɻֲ̿�����������վ������\n");
          if ( me->query("combat_exp") > 120000)
              return notify_fail("�㻹��ȥ�����϶��Щ������ο��ʦ�ɣ�\n");
          if ( me->query_temp("bishou") < 2 ){
            if(objectp(present("bi shou", me)))        
                return notify_fail("�㷢�ֺ������Ѿ��յ����ģ�ʲôҲû���ˡ�\n");   
            me->add_temp("bishou", 1);

            message_vision(HIY"$N���������ض��ż�̳����ͷ����\n"NOR, me);
            return 1;
          }                      
          message_vision(YEL"��̳����ת����$N�������С�������ó�һ��ذ�ס�\n"NOR, me);
          me->delete_temp("bishou");
          new(__DIR__"obj/bishou")->move(me);
          return 1;
        }
        return notify_fail("�����ʲô��ͷ����\n");
}
