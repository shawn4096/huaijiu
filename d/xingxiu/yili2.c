// /d/xingxiu/yili2.c

inherit ROOM;
#include <ansi.h>
void quarter_pass();

void create()
{
        set("short", "���������");
        set("long", @LONG
�������������ģ�����������ʮ�����֡�ֻ�Ƕ���ά������ˣ���
��˵�Ļ��������������С���ϣ������������ٻ����ͣ���������������
��һ�����̣���������һ�Ҳ����������ǳ������Ŀ�ջ�������������
�����ˡ�
LONG
        );
        set("exits", ([ 
        	"west" : __DIR__"store",
        	"east" : __DIR__"house",
        	"northwest" : __DIR__"kezhan",
        	"south" : __DIR__"yili1",
        	"north" : __DIR__"store1",
        ]));
        set("objects", ([
                __DIR__"npc/woman": 1,
                __DIR__"npc/hman": 1,
                __DIR__"npc/wujiang": 1,
         ]));
     
        set("outdoors", "yili");

        set("coor/x",-300);
  set("coor/y",160);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",160);
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
�������������ģ�����ҹ��ȴ������������ʮ�����֡�ֻ�Ƕ���
ά������ˣ�����˵�Ļ��������������С���ϣ������������ٻ����ͣ�
����������������һ�����̣���������һ�Ҳ����������ǳ������Ŀ�
ջ���������������Ѿ����ϡ�
LONG);       
        	  delete("exits/south");
                  break;
            default: set("long", @LONG
�������������ģ�����������ʮ�����֡�ֻ�Ƕ���ά������ˣ���
��˵�Ļ��������������С���ϣ������������ٻ����ͣ���������������
��һ�����̣���������һ�Ҳ����������ǳ������Ŀ�ջ�������������
�����ˡ�
LONG);
                  set("exits/south", __DIR__"yili1");
        	  break;            
        }
        call_out("quarter_pass", 60);
}


