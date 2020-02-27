require 'pry'
require 'awesome_print'

def fac(n)
  (1..n).inject(1, &:*)
end

def wife(n, k)
  k = [k, n - 1].min
  result = n.times.to_a.permutation.map do |seq|
    best = seq[0...k].max || -1
    found_idx = k + (seq[k...n].index { |x| x > best } || (n - k))
    seq[found_idx] == n - 1 ? 1 : 0
  end.sum
  (result.to_f / fac(n)).round(3)
end

def best_wife(n)
  values = n.times.map { |k| wife(n, k) }
  idx = values.index(values.max)
  [n, idx, values[idx], values]
end

def measure
  time_start = Time.now
  result = yield
  time_end = Time.now
  [result, time_end - time_start]
end

(1..10).each do |n|
  p measure { best_wife(n) }
end
