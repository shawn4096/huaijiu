// name.c

#include <ansi.h>
#include <dbase.h>
#include <condition.h>

nosave string *my_id;

void set_name(string name, string *id)
{
        set("name", name);
        set("id", id[0]);
        my_id = id;
}

int id(string str)
{
        string *applied_id;

        if( this_player() && !this_player()->visible(this_object()) ) return 0;

    	reset_eval_cost();
        if( pointerp(applied_id = query_temp("apply/id")) 
        &&      sizeof(applied_id) ) 
                if( member_array(str, applied_id)!=-1 )
                        return 1;
                        
        // If apply/id exists, this object is "pretending" something, don't
        // recognize original id to prevent breaking the pretending with "id"
        // command.

        if( pointerp(my_id) && member_array(str, my_id)!=-1 )
                return 1;
        else
                return 0;
}

string *parse_command_id_list()
{
        string *applied_id;

        if( pointerp(applied_id = query_temp("apply/id")) 
        &&      sizeof(applied_id) )
                return applied_id;
        else
                return my_id;
}

varargs string name(int raw)
{
        object me = this_object();
        object ob = this_player();
        string str, *mask;
        
        if( !raw && sizeof(mask = query_temp("apply/name")) )
                return mask[sizeof(mask)-1];
        if (!raw && wizardp(me))
                if (intp(query("env/invisibility"))
                && query("env/invisibility") > 0)
                        if ((ob && !ob->visible(me)) || ob==me) return "ĳ��";
                        else return "�����"+query("name");
        if( stringp(str = query("name")) )
                return str;
        return file_name(me);
}

varargs string short(int raw)
{
    	object me = this_object();
    	string force;
    	mapping msg;
    	string title, nick, str, art, *mask;
        
        if( !stringp(str = query("short")) )
        if (query("color"))
            	str = query("color") + name(raw) + NOR "(" + capitalize(query("id")) + ")";
        else
            	str = name(raw) + "(" + capitalize(query("id")) + ")";

        if( !me->is_character() ) return str;

    	if( !raw && sizeof(mask = query_temp("apply/short")) )
                str = (string)mask[sizeof(mask)-1];
        else {
                if( stringp(nick = query("nickname")) )
                        str = sprintf("��%s��%s", nick, str);

		if( stringp(art = query("artname")) )
                        str = sprintf("%s%s%s", art, (nick?"":" "), str);
                        
                else if( stringp(title = query("title")) )
                        str = sprintf("%s%s%s", title,(nick?"":" "), str);
        }

        if (!raw) {
        	if ((int)query_temp("pending/exercise")) {
          		force = me->query_skill_mapped("force");
          		if (force) msg = SKILL_D(force)->exercise_msg(me);
          		if (!msg || undefinedp(msg["status_msg"]))
            			str = name() + "������������";
          		else	str = msg["status_msg"];
        	} 
        	else if ((int)query_temp("pending/respirate"))
            		str = name() + "������������";
               	else if ((int)query_temp("pending/heal"))
               		str = name() + "�����˹�����";
               	else if ((int)query_temp("pending/lingwu"))
               		str = name() + "����������ѧ";
        }
        
        if( !raw || wiz_level(me) ) {
                if( me->is_ghost() ) str = HIB "(����) " NOR + str;
                if( me->query("no_pk") ) str = HIY "(��������) " NOR + str;
                if (userp(me) && me->query_condition("killer"))
                        str = HIR "(ͨ����) " NOR + str;
                if( query_temp("netdead") ) str += HIG " <����" + CHINESE_D->chinese_time(uptime() - query_temp("netdead")) + ">" NOR;
                if( in_input() ) str += HIC " <����������>" NOR;
                if( in_edit() ) str += HIY " <�༭������>" NOR;
                if( interactive(me) &&  query_idle( me ) > 120 )
                        str += HIM " <����" + CHINESE_D->chinese_time(query_idle(me)) + ">" NOR;
                if ( me->is_fighting() ) str += HIR " <ս����>" NOR;
                if( !living(me) ) str += HIR + query("disable_type") + NOR;
        }

        return str;
}

varargs string long(int raw)
{
        string str, extra, *mask;
        
        if( !raw && sizeof(mask = query_temp("apply/long")) )
                str = mask[<1];
        else {
                if( !stringp(str = query("long")) )
                        str = short(1) + "\n";
                else str = short(1) + "\n" + str;
        }

        if( stringp(extra = this_object()->extra_long()) )
                str += extra;

        return str;
}

