// Room: /d/xingxiu/yili1.c
// by snowman@SJ

#include <ansi.h>
inherit ROOM;

void quarter_pass();

void create()
{
        set("short", "�������");
        set("long", @LONG
���磬������Զ����ͨ��˹���ϵ����ã��������ء���������������
����ͨ��Ҫ�壬��˿��֮·����Ҫ����վ֮һ�������ǽ������ӱ�����
�ض������Ǹ�һ���ģ�������Ҫ����ǽ����������̨��ǹ�ۣ��䱸ɭ�ϡ�
LONG
        );
        set("outdoors", "yili");
        set("exits", ([
                "south" : __DIR__"yilihe",
                "north" : __DIR__"yili2",
        ]));

        set("objects", ([
                __DIR__"npc/bing" : 2,
                __DIR__"npc/shangren" : 1,
        ]));
        set("coor/x",-300);
  set("coor/y",150);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",150);
   set("coor/z",0);
   setup();
        quarter_pass();
}

void quarter_pass()
{
        string local;
    
        local = NATURE_D->query_daytime();
        
        switch(local){
            case "event_night":
            case "event_midnight": 
                  set("long", @LONG
���磬������Զ����ͨ��˹���ϵ����ã��������ء���������������
����ͨ��Ҫ�壬��˿��֮·����Ҫ����վ֮һ�������ǽ������ӱ�����
�ض������Ǹ�һ���ģ�������Ҫ����ǽ����������̨��ǹ�ۣ��䱸ɭ�ϡ�
������ҹ�䣬�����ѹأ�ֻ�м�������ʿ���ڳ��ſ���ҹ��
LONG);       
        	  delete("exits/north");
                  break;
            default: set("long", @LONG
���磬������Զ����ͨ��˹���ϵ����ã��������ء���������������
����ͨ��Ҫ�壬��˿��֮·����Ҫ����վ֮һ�������ǽ������ӱ�����
�ض������Ǹ�һ���ģ�������Ҫ����ǽ����������̨��ǹ�ۣ��䱸ɭ�ϡ�
LONG);
                  set("exits/north", __DIR__"yili2");
        	  break;            
        }
        call_out("quarter_pass", 60);
}
