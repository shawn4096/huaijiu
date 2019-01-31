#include "/doc/help.h"
#include <ansi.h>
#include <mudlib.h>
#include <group.h>

inherit F_CLEAN_UP;

string *default_search = DEFAULT_SEARCH_PATHS;

int main(object me, string arg )
{
        int i, j;
    	string file, *search, dir;

    	if( !arg ) 
    	{
            	cat( HELP_DIR + "help/topics" );
        	return 1;
    	}
        
        seteuid( getuid() );
        
    	if( arg == "map" ) 
    	{
    		dir = "/help/map/";
    		search = get_dir(dir);
    		i = sizeof(search);
    		if( !i ) 
    			return notify_fail("Ŀǰ��ͼ�ļ���û׼���á�\n");
        	file = "Ŀǰ�������µ����ĵ�ͼ��";
    		for(j = 0; j < i; j++){
                	if ( j % 3 == 0 )
                		file += "\n\t";
                	file += sprintf("%-12s\t\t", search[j]);
                }
            	file += "\n����� help map xxx �ĸ�ʽ�鿴�����ͼ��\n";
        	me->start_more( file );
        	return 1;
          
        }  
        
	if( sscanf(arg, "map %s", arg) ) 
    	{
        	if( !file_size("/help/map/"+arg) )
        		return notify_fail("Ŀǰ��û����������ĵ�ͼ�ļ���\n");
        	me->start_more( read_file("/help/map/" + arg) );
        	return 1;
          
        }  
        
    	arg = ALIAS_D->process_global_alias( arg );
    	if( stringp( file = me->find_command( arg )) ) 
    	{
                notify_fail("�����ָ����ڣ���û��˵���ļ���\n");
        	return write( HIY"��"HIW+CHINESE_MUD_NAME+HIY"��"NOR"\n") + file->help( me );
    	}

    	if( pointerp( search = me->query( "help_search_path" ) ) ) 
    	{
        	i = sizeof(search);
        	while( i-- )
                {
                        if( file_size( search[i] + arg) > 0 ) 
                        {
                                me->start_more( read_file(search[i] + arg) );
                                return 1;
                        }
                }
    	}

    	sscanf(arg, "%s()", arg);
    	if( pointerp(default_search) ) 
    	{
            	i = sizeof(default_search);
        	while(i--) 
                {
                        if( file_size(default_search[i] + arg)>0 ) 
                        {
                            	me->start_more( read_file(default_search[i] + arg) );
                            	return 1;
                        }
                }
    	}

    	if( sscanf(arg, "group %s", arg) ) 
    	{
            	dir = GROUP_DIR + arg + "/";
        	if( file_size(dir) != -2 )
                	return notify_fail("û��������ɡ�\n");
        	if( file_size(dir + "story") < 0 )
                	return notify_fail("�������û�м�顣\n");
        	me->start_more(HIY"��"HIW+CHINESE_MUD_NAME+HIY"��"NOR"��"
                + find_object(dir + "kingdom")->query("kingdom_name") + "\n"NOR
            	+ read_file(dir+"story"));
            	return 1;
    	} 
    	return notify_fail("û��������������˵���ļ���\n");
}

int help(object me)
{
    	write(@HELP
----------------------------------------
ָ���ʽ��help <����>

help <��������>
      
���磺> help cmds

���ָ���ṩ�����ĳһ�������ϸ˵���ļ������ǲ�ָ�����⣬
���ṩ���й�������ļ���

help map
�鿴��ͼ

help group <��������>
�鿴���ɼ��
----------------------------------------
HELP
        );
    	return 1;
}

