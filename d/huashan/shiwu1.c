// Room: /d/huashan/shiwu1.c
// Date: Look 99/03/25

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
һ�䲻���չ��ʯ�ң�ǽ������Ƕ�ż�֦���ͻ�ѣ�ʹ�������ǻ�ƵĹ�
�Ρ����˵�Ψһ�о���Ҳ����������ڴ˾����������ϵĽ������衣
LONG
	);

	set("exits", ([ /* sizeof() == 3 */
	       "east" : __DIR__ "jiabi",
           ]));
   	setup();
}

 void init()
{
    add_action("do_lingwu","comprehend");
}

int do_lingwu(string arg)
{
    object me=this_player();
    int sl,dl;
    if (arg!="sword") return notify_fail("��Ҫ����ʲô��\n");
         if(!me->query("fengset")) return notify_fail("��Ƿ���ǰ���ĵ��ӣ������ڴ�����\n");
    if (me->is_busy() || me->is_fighting()) return notify_fail("����æ���ء�\n");
     sl=(int)me->query_skill("sword",1);
     dl=(int)me->query_skill("dugu-jiujian",1);
     if (!dl)
     return notify_fail("�������¾Ž����ܾ�ʽ��û��˵����Ϲ����ʲô?\n");
       if (sl > me->query("jing") || me->query("jing")*100/me->query("max_jing") < 50) {
                me->receive_damage("jing",sl/2);
                return notify_fail("��û�취���о���\n");
        }
if (dl>=150)
        	{
                if (((int)me->query("max_pot") - 100 - (int)me->query_skill("huashan-jianfa",1) < dl) && dl < 350)
	                return notify_fail("ѧϰ���¾Ž����������𣬿�����Ļ�ɽ������ϰ̫��޷��������������Ľ����ˡ�\n");
		}
      if (sl < dl)
      return notify_fail("��Ļ����������費�����޷��������һ��Ķ��¾Ž����⡣\n");
      if((int)me->query("potential", 1) < 5 )
      return notify_fail("�����ڵ�Ǳ�ܲ�����������¾Ž���\n");
      write(CYN"��ĬĬ���:������������������ͬ�ˣ�ͬ�������С���ת����
           ��ת������ת��ӳ�֮��������֮������δ֮����������һ�䣬
           ɽ����һ�䣬ˮ����һ�䡣Ǭ���༤������༤�������༤��
           ���������壬�������ɾš�����\n"NOR);
     if( me->query_skill("dugu-jiujian",1 ) < 200)
     me->add("potential", -random(5));
     me->improve_skill("dugu-jiujian", random(me->query_int())*10+1);
     me->start_busy(random(2));
     return 1;
 }
