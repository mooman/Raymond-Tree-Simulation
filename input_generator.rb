#!/usr/bin/ruby

nsites = ARGV[0].to_i
max_time = ARGV[1].to_i
nevents = ARGV[2].to_i

puts nsites
puts max_time

events = []

(0...nevents).each do
    events << [rand(max_time), rand(nsites), 'r']
end

events.sort! {|a,b| a[0] <=> b[0]}

events.each do |e|
    puts e.join(' ')
end
