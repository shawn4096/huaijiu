// wu1.c ���䳡
// Modify By River@SJ 99.06
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{ 
       set("short",CYN"���䳡"NOR);
       set("long", @LONG
���������̵����䳡�������Ǽ�Ӳ��ʵ�Ļ��������аٶ���ļ���ʹ�õ�
��⻬ƽ�������䳡�м������Ų���������������ľ�С��ܶ����̽���������
ϰ���ա����������̵�ҩ���������߾�����Ժ�ˡ�
LONG);    
	set("exits", ([
		"east" : __DIR__"yaofang",
                "west" : __DIR__"shuyuan",
                "south" : __DIR__"guangc",
		"north" : __DIR__"xting",
	]));             
	set("objects",([
		__DIR__"npc/f-dizi" : 1,
		__DIR__"npc/m-dizi" : 1,
                CLASS_D("mingjiao") + "/zhang" : 1,
	]));
        set("outdoors", "���̹�����");
        set("coor/x",-290);
  set("coor/y",200);
   set("coor/z",120);
   set("coor/x",-290);
 set("coor/y",200);
   set("coor/z",120);
   setup();
}