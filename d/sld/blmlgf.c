// blmlgf.c
// ������������
inherit ROOM;
void create()
{
	set("short","������");
	set("long",@long
�˴��ǰ����Ž���ƽʱ����ϰ��ĵط������п�ǽ�и������ܣ�����
���Ų��ٱ������Ա߷��ż���ʯ���������м���һ��÷��׮�����ӵĴ���
������ż���ɳ����
long);
	set("exits",([
	    "east" : __DIR__"blm",
]));
	set("objects",([
		__DIR__"npc/obj/bian" : 2,
]));
        set("coor/x",510);
  set("coor/y",420);
   set("coor/z",70);
   setup();
}
	    	
