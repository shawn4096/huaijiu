// longwang.c ������
// Modify By River@SJ 99.06
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{ 
       set("short",MAG"������"NOR);
       set("long", @LONG
������רΪ���������������˿������еҲ�����޼ɽ���Ϊ�ټ�����
������ʾ����ȥ�񡢳��������Ľ�ּ֮�����������һ���㰸�����궼������
ȼ�ţ�����Ѭ����ͷ�����εġ�
LONG);    
	set("exits", ([
		"east" : __DIR__"jyt",
		"west" : __DIR__"tuqi",
                "northwest" : __DIR__"yuanzi",
	]));    

        set("objects",([
		__DIR__"npc/f-dizi" : 1,
                __DIR__"npc/m-dizi" : 1,
                CLASS_D("mingjiao") + "/yang" : 1,
	]));         
        set("coor/x",-240);
  set("coor/y",260);
   set("coor/z",120);
   set("coor/x",-240);
 set("coor/y",260);
   set("coor/z",120);
   setup();        
}

int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}


int valid_leave(object me, string dir)
{
       mapping myfam;
       object ob,*obj;
       object *inv = deep_inventory(me);
       myfam = (mapping)me->query("family");
       ob = present("yang xiao", environment(me));
       if(dir == "northwest" && ( !ob || !living(ob)))
            return notify_fail(YEL"\nͻȻһ������������������ô�����ʹŮ���Ĺ뷿��ɱ��\n\n"NOR);
       if(dir == "northwest" && !myfam && present("yang xiao", environment(me)))
            return notify_fail("���а���һ����ס���ȥ·���ô���Ů���Ĺ뷿��ɱ��\n");
       if((!myfam || myfam["master_name"] != "���޼�" || !me->query_temp("mj_jiaozhu"))
          && dir == "northwest" 
          && objectp(present("yang xiao", environment(me))))
            return notify_fail(YEL"\n���а���һ����ס���ȥ·����������Ů���Ĺ뷿����׼���Խ��룡\n\n"NOR);
       obj = filter_array(inv,(:get_object:));
       if( sizeof(obj) && dir =="northwest" && objectp(ob))
            return notify_fail(YEL"\n���а���һ����ס���ȥ·������ֻ������һ�˽����ص��У�\n\n"NOR);
       return ::valid_leave(me, dir);
}
