/*
 * File:   playerstats.h
 * Author: Kai Mallea <kmallea@gmail.com>
 *
 * Created on December 1, 2014, 5:11 PM
 */

#ifndef PLAYERSTATSTABLE_H
#define	PLAYERSTATSTABLE_H

#include <string>
#include <vector>
#include <map>

struct round_stats
{
    int  kills;
    int  deaths;
    int  assists;
    int  headshots;
    bool mvp;
};

// UserID -> round -> round_stats
typedef std::map< int, std::map< int, round_stats > > round_stats_map_t;

class PlayerStatsTable
{
public:
    PlayerStatsTable() {};
    ~PlayerStatsTable() { map_.clear(); };
    void setRound( int round ) { round_ = round; }
    void addKill( int userID, bool headshot = false ) {
        ++map_[ userID ][ round_ ].kills;
        if (headshot) addHeadshot( userID );
    }
    void addAssist( int userID ) { ++map_[ userID ][ round_ ].assists; }
    void addDeath( int userID ) { ++map_[ userID ][ round_ ].deaths; }
    void addHeadshot( int userID ) { ++map_[ userID ][ round_ ].headshots; }
    void setMvp( int userID ) { map_[ userID ][ round_ ].mvp = true; }
    void displayRoundStats( int round ) {
        printf( "Round %d Stats\n", round );
        printf( "UserID\tK\tD\tA\tHS\tMVP\n" );
        for ( const auto& kv : map_ ) {
            const round_stats& rs = map_[ kv.first ][ round ];
            printf( "%d\t%d\t%d\t%d\t%d\t%d\n", kv.first, rs.kills, rs.deaths,
                    rs.assists, rs.headshots, rs.mvp );
        }
    }
    void displayMatchStats() {
        printf( "Match Stats\n" );
        printf( "UserID\tK\tD\tA\tHS\tMVP\n" );
        for ( const auto& kv : map_ ) {
            int k = 0, d = 0, a = 0, hs = 0, mvp = 0;
            for ( const auto& kv2 : kv.second ) {
                const round_stats& rs = kv2.second;
                k += rs.kills;
                d += rs.deaths;
                a += rs.assists;
                hs += rs.headshots;
                mvp += rs.mvp;
            }
            printf( "%d\t%d\t%d\t%d\t%d\t%d\n", kv.first, k, d, a, hs, mvp );
        }
    }
    void reset() { map_.clear(); }
private:
    int round_;
    round_stats_map_t map_;
};

#endif	/* PLAYERSTATSTABLE_H */
