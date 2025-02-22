// inquiryd.c
// Created by Annihilator@ES2 (01-19-95)
// Modified by Xiang for XKX (12/20/95)
// Modified by snowman@SJ 20/06/2000

// This function handles the default inquiry between ppls and npcs to
// make npc more talktive. This is the '<me> ask <ob> about <topic>'
// case.

#include <ansi.h>

string find_gf_wanted_target(mapping target, int shen)
{
        object npc, where;
	string place;
	
	if( !mapp(target) || !objectp(target["base"]) || !stringp(target["name"]) )
		return "这文书上的字迹模糊不清，我知道你要找谁？？";

	npc = target["base"];
	if( !npc || !objectp(npc) ){
        	if ( shen )
        		return "哦，这个我就不清楚了，这附近没见过"+target["name"]+"这人。";
        	else 	return target["name"]+"？没见过。我忙着呢，你快走开，别在这里烦我！";
        }
        
        where = environment(npc);
        if ( !where ){
        	if ( shen )
        		return target["name"]+"？见过！见过！可这人往哪走了呢？看我这记性，想不起来了！";
        	else 	return "你找"+target["name"]+"是吧？嘿嘿，我见过，可就不告诉你！";
        }     
        if( userp(where) ){
        	place = where->name();
        	if ( shen )
        		return target["name"]+"？刚才听人说被"+place+"抓去了！";
        	else 	return "想找"+target["name"]+"？！你可来晚啦，刚被"+place+"抓走！";
        }
        if( strsrch(base_name(where), "/d/") != 0 )
        	return "不清楚，你到别出找找去吧。";
        if( strsrch(base_name(where), "/d/city/") == 0 )
        	return "没听说过，你到别出找找去吧。";
        if( !stringp(place = TASK_D->get_regions(base_name(where))) )
        	place = environment(npc)->query("short");
        else if( random(5) == 1 )
        	place += environment(npc)->query("short");
        if ( shen )
        	return target["name"]+"是吧？我好象听人说这人在"+place+"附近转悠呢！";
        else 	return "你想找"+target["name"]+"？！哈哈！这人在"+place+"附近，你快去送死吧！";
}


int parse_inquiry(object me, object ob, string topic)
{
	object wenshu;
	mapping target;
	
	switch( topic ) {
		case "name":
		case "姓名":
			message_vision(CYN "$N向$n问道：敢问" + RANK_D->query_respect(ob) + "尊姓大名？\n" NOR, me, ob);
			return 1;
		case "here":
		case "此地":
			message_vision(CYN "$N向$n问道：这位" + RANK_D->query_respect(ob) + "，"
			+ RANK_D->query_self(me) + "初到贵宝地，不知这里有些什么风土人情？\n" NOR, me, ob);
			return 1;
		case "rumors":
		case "传闻":
			message_vision(CYN "$N向$n问道：这位" + RANK_D->query_respect(ob)
			+ "，不知最近有没有听说什么消息？\n" NOR, me, ob);
			return 1;
		case "wanted":
		case "通缉犯":
			if( !userp(me) ) return 0;
			if( !objectp(wenshu = present("tiebu wenshu", me)) ) return 0;
			if( strsrch(base_name(environment(ob)), "/d/city/") == 0 ) return 0;
			message_vision(CYN "$N向$n问道：这位" + RANK_D->query_respect(ob)
				+ "，不知最近有没有铁捕文书里这个通缉犯的消息？\n" NOR, me, ob);
			me->receive_damage("jingli", 50+random(100), "精力消耗完毕而");
			if( random(15) < 10 ) return 1;
			if( wenshu->query("asked_times") >= 3 ) return 1;
			if( !mapp(target = wenshu->query("target")) )
				ob->set("inquiry/" + topic, "笑话，你拿张空白的文书来找"+RANK_D->query_self(ob)+"开心啊？");

			else ob->set("inquiry/" + topic, find_gf_wanted_target(target, ob->query("shen") > 0));
			wenshu->add("asked_times", 1);
			call_out("del_inquiry", 1 , ob, topic);
			return 1;
		default:
			return 0;
	}
}

void del_inquiry(object ob, string topic)
{
	if( !ob ) return;
	ob->delete("inquiry/" + topic);
}

