inherit ROOM;

void create()
{
        set("short", "��ʯ�ٵ�");
        set("long",@long
������һ����ʯ����ϣ����������ǳ���æ����ʱ����������ҴҶ�����
����ͨ�����ݳǡ��������Ǽ��˳ǡ�
long);
	set("outdoors", "����");                        
/*	set("objects",([
		__DIR__"npc/yetu" : 1,
	]));*/
	set("exits",([
		"northwest" : __DIR__"road2",
		"southeast" : __DIR__"jiaxing",
	]));
	set("coor/x",130);
  set("coor/y",-290);
   set("coor/z",0);
   setup();
}
