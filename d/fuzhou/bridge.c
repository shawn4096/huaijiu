// by xiaoyao

inherit ROOM;

void quarter_pass();

void create()
{
        set("short","���ŵ���");
        set("long",@LONG
���Ǹ��������һ�����ţ��Ӱ��Ž��������ĳ�¥����������
������άϵ���ճ����µ���������𡣹������������߿ɴ����Ϲ�
����
LONG);
        set("outdoors", "����");
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/foshan/road14",
            "north"  : __DIR__"nanmen",
        ]));
        set("no_clean_up", 0);
        set("coor/x",100);
  set("coor/y",-490);
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
�����Ǹ��ݵ����ţ������Ϸ������ͨ����ɽ�򣬿�ϧ���սٷ�������
�������������ڸ��ݳ���ĵ����Ѿ����£������Ĺ�·��ֻ�ܵȵ����ղ��ܽ�
��ǳء�
LONG);       
        	  delete("exits/north");
                  break;
            default: set("long", @LONG
���Ǹ��������һ�����ţ��Ӱ��Ž��������ĳ�¥����������������άϵ��
�ճ����µ���������𡣹������������߿ɴ����Ϲ㶫���������˻��࣬����
�����쳣��æ��
LONG);
                  set("exits/north", __DIR__"nanmen");
        	  break;            
        }
        call_out("quarter_pass", 60);
}

