// foubing.c ��ɽ
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short",HIW"��ɽ"NOR);
	set("long", @LONG
����һ��ܴ󸡶���ɽ����������������ɡ�����ǰ��ı�ɽ�ܵ���ɽ֮
�ȣ����ϵ��ۻ�������������������ม�����ϵ����������Ա�ɽ�ǲ��ϵĿ�
����ɽ��
LONG);
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_sleep_room", 1); 
        set("outdoors","����");
	setup();
}

void run(object ob)
{
       if(objectp(present(ob, this_object()))){
  	  write(HIW"\n��ɽ��������Ʈȥ��\n\n"NOR);
       	  ob->move(__DIR__"foubing1");
       }
}

void init()
{
    if(interactive(this_player())){
          remove_call_out("run");
          call_out("run", 20+random(30), this_player());
       }
}
