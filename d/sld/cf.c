// cf.c
// ����
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@long
�����������̽��ڳԷ���ˮ�ĵط�����̨�Ϸ��Ų��ٰ��ӡ��ƴ���
long);
	set("exits",([
           "west" : __DIR__"th",          
]));
       set("objects",([
		__DIR__"npc/chuzi" : 1,
		__DIR__"npc/obj/baozi" : 3,
		__DIR__"npc/obj/jiudai" : 3,
]));

	set("coor/x",530);
  set("coor/y",450);
   set("coor/z",90);
   setup();
}
	    	
