// tulu1.c
// By Jpei

inherit ROOM;

void create()
{
        set("short", "��·");
        set("long",@long
��������һ����·�ϣ����ϱ߲�Զ������������������ȥ���ݵĹٵ���
long);
	set("outdoors", "suzhou");
	set("exits",([
		"north" : __DIR__"qsgdao5",
		"southwest" : __DIR__"tulu2",
	]));
	set("coor/x",60);
  set("coor/y",-220);
   set("coor/z",0);
   setup();
}
