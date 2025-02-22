// emoted.c
// Modify by Yu Jue 1998-3-5, 优化速度

#include <ansi.h>

inherit F_SAVE;

mapping emote;

//	The emote mapping contains the data base of emote definitions. Each emote
//	is defined in a sub-mapping with the following structure:
//
//	myself	- the message emoter will see
//	target	- the message the target will see when targeted
//	others	- the message others will see when no argument.
//
//	The emote mapping is indexed with the emote 'pattern' instead of emote
//	verb. For example, typing "smile" without argument will cause the daemon
//	search the emote mapping with "smile" as key, and typing "smile someone"
//	will cause the daemon search the emote mapping with "smile $" pattern as
//	the key, while $ means one argument.
//
//	In the message string, the following substitutions will be applied before
//	sending the messages:
//
//	$N		- name of emoter
//	$n		- name of target
//	$P		- pronoun of emoter
//	$p		- pronoun of target
//
//	Original by Annihilator@ESII (11/09/94)
//      $C              - very close call of emoter
//      $c              - close call of target
//      $R              - respect calling of target
//      $r              - rude calling of target
//      $S              - self calling of emoter
//      $s              - self-rude calling of emoter

void create()
{
	seteuid(getuid());
	if( !restore() && !mapp(emote) )
		emote = ([]);
}

string query_save_file() { return DATA_DIR + "emoted"; }

// command_hook() of F_COMMAND call this as an alternate command processor.
// CHANNEL_D also calls this to get emote message.
varargs mixed do_emote(object me, string verb, string arg, int channel_emote, string who)
{
	string str, my_gender, target_gender, msg_postfix;
	object target;

	if( !environment(me) ) return 0;

	if ( !mapp(emote) || undefinedp(emote[verb]) ) return 0;

	notify_fail("你要对谁做这个动作？\n");
	// Determine the pattern to be searched and the target.
	if ( stringp(arg) && arg != "" ) {
		target = present(arg, environment(me));

		if(!objectp(target)) {
			// If not channel emote, only search target in our environment.
			if(!channel_emote) return 0;
			target = LOGIN_D->find_body(arg);
			if( !objectp(target) ) return 0;
		}

		if( !target->is_character() || !me->visible(target) )
			return 0;
		if (wiz_level(me) < wiz_level(target) && target->query("env/no_emote"))
			return 0;

		target_gender = target->query("gender");
		if (target == me) {
			msg_postfix = "_self";
			target = 0;
		} else msg_postfix = "_target";
	} else msg_postfix = "";

	my_gender = me->query("gender");
	if (!who)
		who = me->name();

	if ( !channel_emote ) {
		message("wizard", CYN "(" + capitalize(me->query("id")) + ")" NOR, environment(me), me);
		if( stringp(str = emote[verb]["myself" + msg_postfix]) ) {
			str = replace_string(str, "$N", who);
			str = replace_string(str, "$P", gender_self(my_gender));
			str = replace_string(str, "$S", RANK_D->query_self(me));
			str = replace_string(str, "$s", RANK_D->query_self_rude(me));
			if( objectp(target) ) {
				str = replace_string(str, "$C", RANK_D->query_self_close(target, me));
				str = replace_string(str, "$c", RANK_D->query_close(target, me));
				str = replace_string(str, "$R", RANK_D->query_respect(target));
				str = replace_string(str, "$r", RANK_D->query_rude(target));
				str = replace_string(str, "$n", target->name());
				str = replace_string(str, "$p", gender_pronoun(target_gender));
			}
			str = replace_string(str, NOR, CSI+"0m"+CYN);
			message("emote", CYN + str + NOR, me);
		}

		if( objectp(target) && stringp(str = emote[verb]["target"]) ) {
			str = replace_string(str, "$N", who);
			str = replace_string(str, "$P", gender_pronoun(my_gender));
			str = replace_string(str, "$S", RANK_D->query_self(me));
			str = replace_string(str, "$s", RANK_D->query_self_rude(me));
			str = replace_string(str, "$C", RANK_D->query_self_close(target, me));
			str = replace_string(str, "$c", RANK_D->query_close(target, me));
			str = replace_string(str, "$R", RANK_D->query_respect(target));
			str = replace_string(str, "$r", RANK_D->query_rude(target));
			str = replace_string(str, "$n", target->name());
			str = replace_string(str, "$p", gender_self(target_gender));
			str = replace_string(str, NOR, CSI+"0m"+CYN);
			message("emote", CYN + str + NOR, target);
		}
	}

	if( stringp(str = emote[verb]["others"+msg_postfix]) ) {
		str = replace_string(str, "$N", who);
		str = replace_string(str, "$P", gender_pronoun(my_gender));
		str = replace_string(str, "$S", RANK_D->query_self(me));
		str = replace_string(str, "$s", RANK_D->query_self_rude(me));
		if( objectp(target) ) {
			str = replace_string(str, "$C", RANK_D->query_self_close(target, me));
			str = replace_string(str, "$c", RANK_D->query_close(target, me));
			str = replace_string(str, "$R", RANK_D->query_respect(target));
			str = replace_string(str, "$r", RANK_D->query_rude(target));
			str = replace_string(str, "$n", target->name(channel_emote && me != target));
			str = replace_string(str, "$p", gender_pronoun(target_gender));
		}
		if (!channel_emote) {
			str = replace_string(str, NOR, CSI+"0m"+CYN);
			message("emote", CYN + str + NOR, environment(me), ({me, target}));
		} else return str?str[0..<2]:0;
	}

	// Let NPC know we are doing emote on him.
	if( objectp(target) ) target->relay_emote(me, verb);

	return 1-channel_emote;
}

int set_emote(string pattern, mapping def)
{
	emote[pattern] = def;
	save();
	return 1;
}

int delete_emote(string pattern)
{
	map_delete(emote, pattern);
	save();
	return 1;
}

mapping query_emote(string pattern)
{
	if( !undefinedp(emote[pattern]) ) return emote[pattern];
	return ([]);
}

string *query_all_emote()
{
	return keys(emote);
}
